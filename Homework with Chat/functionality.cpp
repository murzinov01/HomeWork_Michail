#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "functionality.h"

#define _CRT_SECURE_NO_WARNINGS
#define FILE_NAME_USERS "users.txt"
#define FILE_NAME_CHATS "chats.txt"
#define COMMANDS_NUM 5
#define MAX_CLIENTS 100
#define MAX_INFO_LEN 20

int* ids;
char** logins;
char** passwords;
int chats_id[MAX_CLIENTS];
int chats_members[MAX_CLIENTS][10] = { 0 };
int online_members[MAX_CLIENTS] = { 0 };

int USERS_NUM = 0;
int CHATS_NUM = 0;

int reg_user(char* login, char* password)
{
	if (strlen(login) > 20 || strlen(password) > 20 || strlen(login) < 3 || strlen(password) < 3)
	{
		return 1; // 1 - не правильная длина
	}

	srand(time(NULL));
	int id = rand() % 899999 + 100000; // от 100 000 до 999 999 (шанс совпасть 0.0001%)
	FILE* users;
	users = fopen(FILE_NAME_USERS, "a+");
	fprintf(users, "%s %s %d\n", login, password, id);
	fclose(users);

	return id;
}

void clear_data()
{
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		free(logins[i]);
		free(passwords[i]);
	}
	free(ids);
	free(logins);
	free(passwords);
}

int read_all_users()
{
	int i = 0;
	FILE* users;
	char id[50] = { '\0' };
	ids = (int*) calloc(MAX_CLIENTS, sizeof(int));
	logins = (char**) calloc(MAX_CLIENTS, sizeof(char*));
	passwords = (char**) calloc(MAX_CLIENTS, sizeof(char*));

	// Выделяем память под матрицу с информацией о клиентах
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		logins[i] = (char*)calloc(MAX_INFO_LEN, sizeof(char));
		passwords[i] = (char*)calloc(MAX_INFO_LEN, sizeof(char));
	}

	users = fopen(FILE_NAME_USERS, "r");
	while (i < MAX_CLIENTS && fscanf(users, "%s %s %s", logins[i], passwords[i], id) != EOF)
	{
		ids[i] = atoi(id);
		i++;
	}
	USERS_NUM = i;
	return i;
}

int read_all_chats()
{
	int chats_num = 0, i = 0, params = 0;
	FILE* chats;
	char chat_id[7] = { '\0' };
	chats = fopen(FILE_NAME_CHATS, "r");

	// Идем по всем чатам
	while (i < MAX_CLIENTS)
	{
		char users[10][50] = { '\0' };
		char string[1024] = { '\0' };
		if (feof(chats) || fgets(string, 1024, chats) == NULL)
			break;
		params = sscanf(string, "%s %s %s %s %s %s %s %s %s %s %s", chat_id, users[0],
			users[1], users[2], users[3], users[4], users[5], users[6], users[7], users[8], users[9]);
		chats_id[i] = atoi(chat_id);
		for (int j = 0; j < params - 1; j++)
		{
			chats_members[i][j] = find_id_by_user(users[j]);
		}
		i++;
	}
	CHATS_NUM = i;

	return i;
}

int check_users(char* user)
{
	for (int i = 0; i < USERS_NUM; i++)
	{
		if (!strcmp(user, logins[i]))
			return 1;						// Если пользователь с таким логином уже есть
	}
	return 0;								// Имя логина свободно
}

int check_password(char* user, char* password)
{
	for (int i = 0; i < USERS_NUM; i++)
	{
		if (!strcmp(user, logins[i]))
		{
			if (!strcmp(password, passwords[i]))
				return ids[i];
		}
	}
	return 0;
}

int check_valid_chat(char args[10][50], int users_num)
{
	int users = 0;
	for (int i = 0; i < users_num; i++)
	{
		for (int j = 0; j < MAX_CLIENTS; j++)
		{
			if (!strcmp(args[i], logins[j]))
			{
				users++;
				break;
			}
		}
	}
	if (users == users_num)
		return 1;
	else
		return 0;
}

int create_chat(char args[10][50], int users_num)
{
	srand(time(NULL));
	int id = rand() % 899999 + 100000;						 // от 100 000 до 999 999 (шанс совпасть 0.0001%)
	FILE* chat;
	FILE* chats;
	char chat_id[11] = { '\0' };

	_itoa(id, chat_id, 10);
	chat_id[6] = '.';
	chat_id[7] = 't';
	chat_id[8] = 'x';
	chat_id[9] = 't';

	chat = fopen(chat_id, "w");
	fclose(chat);

	chats = fopen(FILE_NAME_CHATS, "a+");
	fprintf(chats, "%d", id);
	for (int i = 0; i < users_num; i++)
	{
		fprintf(chats, " %s", args[i]);
	}
	fprintf(chats, "\n");

	return id;
}

int find_chat(char args[10][50], int users_num)
{
	// Идем по чатам в бд
	for (int i = 0; i < CHATS_NUM; i++)
	{
		int users_count = 0;
		// Идем по аргументам (юзерам)
		for (int j = 0; j < users_num; j++)
		{
			int id = 0;
			// Находим id для аргумента (юзера)
			id = find_id_by_user(args[j]);
			// Проверяем, есть ли юзер в бд
			for (int k = 0; k < 10; k++)
			{
				if (chats_members[i][k] == 0)
					break;
				if (chats_members[i][k] == id)
				{
					users_count++;
					break;
				}
			}
		}
		if (users_count == users_num)
			return chats_id[i];
	}
	return 0;
}

char* find_user_by_id(int id)
{
	for (int i = 0; i < USERS_NUM; i++)
	{
		if (ids[i] == id)
			return logins[i];
	}
}

int find_id_by_user(char* user)
{
	for (int i = 0; i < USERS_NUM; i++)
	{
		if (!strcmp(user, logins[i]))
			return ids[i];
	}
}

void set_online_status(int id, int status)
{
	for (int i = 0; i < MAX_CLIENTS; i++)
		if (id == ids[i])
		{
			online_members[i] = status;
			break;
		}
}

int count_online(int chat_id)
{
	int counter = 0;
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		// Ищем чат
		if (chats_id[i] == chat_id)
		{
			// Идем по всем учатникам
			for (int j = 0; j < 10; j++)
			{
				// Смотрим, есть ли они в таблице юзеров на данный момент
				for (int k = 0; k < MAX_CLIENTS; k++)
				{
					if ((ids[k] == chats_members[i][j]) && online_members[k])
					{
						counter++;
						break;
					}
				}
			}
			break;
		}
	}
	return counter;
}

COMMAND command_definer(char* string) {
	COMMAND my_command;
	my_command.command_num = MISTAKE;

	if (string[0] != '-')
	{
		strcpy(my_command.message, string);
		my_command.command_num = MESSAGE;
		return my_command;
	}

	const char* const commands_list[] = {
	"-help\0", "-reg\0", "-login\0", "-chat\0", "-chat_exit\0", 0
	};

	char buf_command[11] = { '\0' };

	my_command.args_num = sscanf(string, "%s %s %s %s %s %s %s %s %s %s", buf_command, my_command.args[0], my_command.args[1], my_command.args[2],
								 my_command.args[3], my_command.args[4], my_command.args[5], my_command.args[6], my_command.args[7], my_command.args[8]) - 1;

	for (int c_i = 0; c_i < COMMANDS_NUM; c_i++)
	{
		if (!strcmp(buf_command, commands_list[c_i]))
		{
			my_command.command_num = c_i + 1;
			break;
		}
	}

	return my_command;
}