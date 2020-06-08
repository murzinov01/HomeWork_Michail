// server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// #include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#define HAVE_STRUCT_TIMESPEC
#define MAX_SLOTS 5
#include <pthread.h>
#pragma comment(lib, "ws2_32.lib")
#include <winsock.h>
#include <stdio.h>
#include "functionality.h"

pthread_mutex_t mutex;

int view_count[MAX_SLOTS] = { 0 };
int author[MAX_SLOTS] = { 0 };
int message_chat_id[MAX_SLOTS] = { 0 };
char messages[MAX_SLOTS][1024] = { '\0' };

void* listener_chat(void* params)
{
	CHAT_PARAMS* parametres = (CHAT_PARAMS*)params;
	SOCKET client = parametres->client_;
	int chat_id = parametres->chat_id;
	int user_id = parametres->user_id;
	while (1)
	{
		for (int i = 0; i < 5; i++)
		{
			if (chat_id == message_chat_id[i] && message_chat_id[i])
			{
				pthread_mutex_lock(&mutex);
				if (author[i] == user_id || !author[i] || !view_count[i])
				{
					pthread_mutex_unlock(&mutex);
					continue;
				}
				//pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
				int ret = send(client, messages[i], sizeof(messages[i]), 0);

				view_count[i]++;
				// pthread_mutex_unlock(&mutex);

				if (ret == SOCKET_ERROR) // если не удалось подключиться к сокету клиента
				{
					//pthread_mutex_lock(&mutex);
					printf("Error sending data\n");
				//	pthread_mutex_unlock(&mutex);
					set_online_status(user_id, 0);
					return (void*)2;
				}
				//pthread_mutex_lock(&mutex);
				//while (view_count[i] < count_online(chat_id))
				//pthread_cond_wait(&cond_var, &mutex);
				//pthread_mutex_unlock(&mutex);
				//pthread_mutex_lock(&mutex);
				if (view_count[i] >= count_online(chat_id))
				{
					author[i] = 0;
					message_chat_id[i] = 0;
					messages[i][0] = '\0';
					view_count[i] = 0;
				}
				pthread_mutex_unlock(&mutex);
				while (view_count[i]);
				break;
			}
		}
	}
}

void* ClientStart(void* param)
{
	SOCKET client = (SOCKET)param;

	int ret, id = 0, chat_id = 0, status_flag = 0;
	FILE* chat_file;
	COMMAND cmnd;
	pthread_t chat_thread;

	while (1)
	{
		char recieve[1024] = { '\0' };
		char transmit[1024] = { '\0' };
		//полчение ответа
		ret = recv(client, recieve, 1024, 0); // Получаем данные сервера. Ответ от него
		//обработка ошибок
		if (ret == 0 || ret == WSAECONNRESET) // Если получили ответ от сервера, закрываем соединение
		{
			pthread_mutex_lock(&mutex);
			printf("Connection closed\n");
			pthread_mutex_unlock(&mutex);
			return (void*)0;
		}
		if (ret < 0) // Если ответ от сервера запаздает, то мы выйдем по ошибке SPCKET_ERROR
			continue;

		recieve[ret] = '\0'; // символ конца строки в конец строки

		cmnd = command_definer(recieve);
		if (cmnd.command_num == HELP)
			sprintf_s(transmit, "%d %s\n", COMMAND_HELP, "");
		else if (!id && cmnd.command_num != LOGIN && cmnd.command_num != REG)
			sprintf_s(transmit, "%d %s\n", NEED_AUTH, "Need authentication! Use -help");
		else
		{
			switch (cmnd.command_num)
			{
			case MISTAKE:
				sprintf_s(transmit, "%d %s\n", COMMAND_MISTAKE, "This command doesn't exist!!");
				break;
			case HELP:
				break;
			case REG:
				if (status_flag == LOGGED)
				{
					sprintf_s(transmit, "%d %s\n", COMMAND_REG_MIS, "You are already logged in. if you want to create a new account, log out of the current one");
					break;
				}
				if (status_flag == REGISTRED)
				{
					sprintf_s(transmit, "%d %s\n", COMMAND_REG_MIS, "The User already registered!");
					break;
				}
				if (check_users(cmnd.args[0]))
				{
					sprintf_s(transmit, "%d %s\n", COMMAND_REG_MIS, "This user name already exists.");
					break;
				}
				sprintf_s(transmit, "%d %s\n", COMMAND_REG_SUC, "The User is successfully registered!");
				status_flag = REGISTRED;
				pthread_mutex_lock(&mutex);
				id = reg_user(cmnd.args[0], cmnd.args[1]);
				read_all_users();
				pthread_mutex_unlock(&mutex);
				break;
			case LOGIN:
				if (status_flag == LOGGED)
				{
					sprintf_s(transmit, "%d %s\n", COMMAND_REG_MIS, "The User is already logged in");
					break;
				}
				if (!check_users(cmnd.args[0]))
				{
					sprintf_s(transmit, "%d %s\n", COMMAND_REG_MIS, "This user does not exist.");
					break;
				}
				id = check_password(cmnd.args[0], cmnd.args[1]);
				if (!id)
				{
					sprintf_s(transmit, "%d %s\n", COMMAND_REG_MIS, "Invalid password!!");
					break;
				}
				sprintf_s(transmit, "%d %s\n", COMMAND_REG_SUC, "The User logged in successfully!");
				status_flag = LOGGED;
				break;
			case CHAT:
				// Если слишком много юзеров
				if (cmnd.args_num > 9)
				{
					sprintf_s(transmit, "%d %s\n", INVALID_CHAT, "Too many users for chat");
					break;
				}
				// Если указали не существующих юзеров
				if (!check_valid_chat(cmnd.args, cmnd.args_num))
				{
					sprintf_s(transmit, "%d %s\n", INVALID_CHAT, "Such user or users are not found!");
					break;
				}
				// Если все хорошо, ставим создателя чата в конец списка юзеров
				strcpy(cmnd.args[cmnd.args_num++], find_user_by_id(id));
				for (int j = cmnd.args_num; j < 10; j++)
					cmnd.args[j][0] = '\0';
				// Нашли чат
				chat_id = find_chat(cmnd.args, cmnd.args_num);
				CHAT_PARAMS listener_params;
				// Если чат не существует - создаем его
				if (!chat_id)
				{
					chat_id = create_chat(cmnd.args, cmnd.args_num);
					set_online_status(id, chat_id);
					listener_params.chat_id = chat_id;
					listener_params.user_id = id;
					listener_params.client_ = client;
					int status = pthread_create(&chat_thread, NULL, listener_chat, (void*)&listener_params); // Создаем новый поток для клиента. (void*)client - указатель на сокет клиента
					pthread_detach(chat_thread);
					sprintf_s(transmit, "%d %s %s %s %s %s %s %s %s %s %s\n\0", VALID_CHAT, cmnd.args[0], cmnd.args[1], cmnd.args[2], cmnd.args[3],
						cmnd.args[4], cmnd.args[5], cmnd.args[6], cmnd.args[7], cmnd.args[8], cmnd.args[9]);
					pthread_mutex_lock(&mutex);
					read_all_chats();
					pthread_mutex_unlock(&mutex);
					break;
				}
				// Если чат существует
				else
				{
					set_online_status(id, chat_id);
					listener_params.chat_id = chat_id;
					listener_params.user_id = id;
					listener_params.client_ = client;
					int status = pthread_create(&chat_thread, NULL, listener_chat, (void*)&listener_params); // Создаем новый поток для клиента. (void*)client - указатель на сокет клиента
					pthread_detach(chat_thread);
					sprintf_s(transmit, "%d %s %s %s %s %s %s %s %s %s %s\n\0", VALID_CHAT, cmnd.args[0], cmnd.args[1], cmnd.args[2], cmnd.args[3],
						cmnd.args[4], cmnd.args[5], cmnd.args[6], cmnd.args[7], cmnd.args[8], cmnd.args[9]);
					ret = send(client, transmit, sizeof(transmit), 0);

					if (ret == SOCKET_ERROR) // если не удалось подключиться к сокету клиента
					{
						pthread_mutex_lock(&mutex);
						printf("Error sending data\n");
						pthread_mutex_unlock(&mutex);
						set_online_status(id, 0);
						return (void*)2;
					}
					char chat_ID[11] = { '\0' };
					_itoa(chat_id, chat_ID, 10);
					chat_ID[6] = '.';
					chat_ID[7] = 't';
					chat_ID[8] = 'x';
					chat_ID[9] = 't';

					chat_file = fopen(chat_ID, "r");
					char start_message[1024] = { '\0' };

					sprintf_s(start_message, "%d", START_HISTORY);
					ret = send(client, start_message, sizeof(start_message), 0);

					if (ret == SOCKET_ERROR) // если не удалось подключиться к сокету клиента
					{
						pthread_mutex_lock(&mutex);
						printf("Error sending data\n");
						pthread_mutex_unlock(&mutex);
						set_online_status(id, 0);
						return (void*)2;
					}

					while (1)
					{
						char message[1024] = { '3', '0', ' ', '\0' };
						//if (fscanf(chat_file, "%s %1000[^\0]", message[3]) == EOF)
						if (feof(chat_file) || fgets(message + 3, 1000, chat_file) == NULL)
						{
							sprintf_s(start_message, "%d", END_HISTORY);
							ret = send(client, start_message, sizeof(start_message), 0);

							if (ret == SOCKET_ERROR) // если не удалось подключиться к сокету клиента
							{
								pthread_mutex_lock(&mutex);
								printf("Error sending data\n");
								pthread_mutex_unlock(&mutex);
								set_online_status(id, 0);
								return (void*)2;
							}
							break;
						}
						else
						{
							ret = send(client, message, sizeof(message), 0);

							if (ret == SOCKET_ERROR) // если не удалось подключиться к сокету клиента
							{
								pthread_mutex_lock(&mutex);
								printf("Error sending data\n");
								pthread_mutex_unlock(&mutex);
								set_online_status(id, 0);
								return (void*)2;
							}
						}
					}
					fclose(chat_file);
					continue;
				}
			case CHAT_EXIT:
				set_online_status(id, 0);
				chat_id = 0;
				pthread_cancel(chat_thread);
				sprintf_s(transmit, "%d %s\n", EXIT_CHAT, "Pokinyla chat, chat, chat, chat...");
				break;
			case MESSAGE:
				pthread_mutex_lock(&mutex);
				char buf[1024] = { '\0' };
				char user_name[50] = { '\0' };
				strcpy(user_name, find_user_by_id(id));
				sprintf(buf, "%d [%s]: %s\n", NEW_MESSAGE, user_name, cmnd.message);
				char chat_Id[11] = { '\0' };
				_itoa(chat_id, chat_Id, 10);
				chat_Id[6] = '.';
				chat_Id[7] = 't';
				chat_Id[8] = 'x';
				chat_Id[9] = 't';

				chat_file = fopen(chat_Id, "a+");
				fprintf(chat_file, "%s", buf + 2);
				fclose(chat_file);
				pthread_mutex_unlock(&mutex);
				if (count_online(chat_id) > 1) {
					for (int i = 0; i < MAX_SLOTS; i++)
					{
						if (!message_chat_id[i])
						{
							strcpy(messages[i], buf);
							message_chat_id[i] = chat_id;
							author[i] = id;
							view_count[i] = 1;
							break;
						}
					}
				}
				continue;
			}
		}

		ret = send(client, transmit, sizeof(transmit), 0);

		if (ret == SOCKET_ERROR) // если не удалось подключиться к сокету клиента
		{
			pthread_mutex_lock(&mutex);
			printf("Error sending data\n");
			pthread_mutex_unlock(&mutex);
			set_online_status(id, 0);
			return (void*)2;
		}
	}

	return (void*)0;
}

int CreateServer()
{
	SOCKET server, client;
	sockaddr_in localaddr, clientaddr;
	int size;

	// Создаем сервер
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (server == INVALID_SOCKET)
	{
		printf("Error create server\n");
		return 1;
	}

	// Связываем сервер с его IP и портом
	// Запускаем сервер по его IP и порту
	localaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // приводим ip адрес к единому стандартному виду
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(5510);// Приводим адрес порта к стандартному виду. port number is for example, must be more than 1024

	if (bind(server, (sockaddr*)&localaddr, sizeof(localaddr)) == SOCKET_ERROR) // Связываем сервер с его IP и портом
	{
		printf("Can't start server\n");
		return 2;
	}
	else
	{
		printf("Server is started\n");
	}

	read_all_users();
	read_all_chats();

	listen(server, 50);//50 клиентов в очереди могут стоять. Сервер слушает порт, с которым мы его связали
	pthread_mutex_init(&mutex, NULL);
	while (1)
	{
		size = sizeof(clientaddr);
		client = accept(server, (sockaddr*)&clientaddr, &size); // Ловим клиента

		if (client == INVALID_SOCKET)
		{
			printf("Error accept client\n");
			continue;
		}

		pthread_t mythread; // Запускаем новый поток для связи с клиентом
		int status = pthread_create(&mythread, NULL, ClientStart, (void*)client); // Создаем новый поток для клиента. (void*)client - указатель на сокет клиента
		pthread_detach(mythread);  // Отстегиваем поток от основного, все потоки сами по себе. Дочерний поток завершается и мы об этом не знаем. Он сам по себе
	}							   // Если основной поток заканчивается, то заканчивается и дочерний
	pthread_mutex_destroy(&mutex); // Разрушаем мютекс ( на всякий случай )
	clear_data();
	printf("Server is stopped\n");
	closesocket(server);
	return 0;
}

int main()
{
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(1, 1), &wsd) == 0) // подключаемся к библиотеки сокетов
	{
		printf("Connected to socket lib\n");
	}
	else
	{
		return 1;
	}
	int err = 0;
	if (err = CreateServer())
	{
		return err;
	}
	return 0;
}