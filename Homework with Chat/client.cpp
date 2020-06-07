// client.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

// #include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#pragma comment(lib, "ws2_32.lib")
#include <winsock.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "client_functionality.h"

pthread_mutex_t mutex1;

#define MAX_SIZE 100

void* ClientListener(void* params)
{
	SOCKET client = (SOCKET)params;
	while (1)
	{

		char message[1024] = { '\0' };
		int ret = recv(client, message, 1024, 0); // �������� ������ �������. ����� �� ����
			//��������� ������
		if (ret == 0 || ret == WSAECONNRESET) // ���� �������� ����� �� �������, ��������� ����������
		{
			printf("Connection closed\n");
			return (void*)0;
		}
		if (ret < 0) // ���� ����� �� ������� ���������, �� �� ������ �� ������ SPCKET_ERROR
			continue;

		RESPONSE my_response = response_definer(message);

		switch (my_response.resp)
		{
		case COMMAND_HELP:
			printf(" -help : show all commands\n -reg : to register in social network(login, password)\n -login : to log in account(login, password)\n -chat : start a chat(users)\n -chat_exit : exit a chat\n");
			break;
		case NEW_MESSAGE:
			printf("%s\n", my_response.message);
			break;
		case VALID_CHAT:
			print_dialog_interface(my_response.message);
			break;
		case START_HISTORY:
			while (1)
			{
				char new_message[1024] = { '\0' };
				ret = recv(client, new_message, 1024, 0); // �������� ������ �������. ����� �� ����
				//��������� ������
				if (ret == 0 || ret == WSAECONNRESET) // ���� �������� ����� �� �������, ��������� ����������
				{
					printf("Connection closed\n");
					return (void*)0;
				}
				if (ret < 0) // ���� ����� �� ������� ���������, �� �� ������ �� ������ SPCKET_ERROR
					continue;
				my_response = response_definer(new_message);
				if (my_response.resp == END_HISTORY)
				{
					printf("\n");
					break;
				}
				else
					printf("\n%s", my_response.message);
			}
			break;
		default:
			printf("[SERVER]: %s\n", my_response.message);
			break;
		}

	}
	return (void*)0;
}

void SendData2Server()
{
	SOCKET client;
	
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_IP); // ������� ����� �������, ��� �� ���������� � ��������
	if (client == INVALID_SOCKET)
	{
		printf("Error create socket\n");
		return;
	}
	sockaddr_in server;														 // ������ ���������� � ������� ��� ����� � ���
	server.sin_family = AF_INET;
	server.sin_port = htons(5510);											 // ���� ��� � �������
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");					 //����������� ������ ������ � �����. special look-up address (������� ������ ����������) // ����� �������
	if (connect(client, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) // ��������� �� ����� ������� ��������� ������, ������� ��������� � �������
	{
		printf("Can't connect to server\n");								// ���� ���-�� ����� �� ���
		closesocket(client);												// ��������� �����
		return;
	}
	char message[1024];														// ������ ��� � ������, ������� ����� ������ - 1024
	pthread_t mythread;
	int status = pthread_create(&mythread, NULL, ClientListener, (void*)client); // ������� ����� ����� ��� �������. (void*)client - ��������� �� ����� �������
	pthread_detach(mythread);

	while (1)
	{
		gets_s(message, 1000);
		//sprintf(message, "asdasd<%d client> %s %d", number, "test", count); // ��������� ������
		int ret = send(client, message, strlen(message), 0);					// �������� ������
		if (ret == SOCKET_ERROR)
		{
			printf("Can't send message\n");
			closesocket(client);
			return;
		}
	}
	closesocket(client); // ��������� ����� ����� �������
}

int main()
{
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(1, 1), &wsd) != 0) // ������������ � ���������� �������
	{
		printf("Can't connect to socket lib");
		return 1;
	}

	SendData2Server(); // ���������� ���� �� ������
	return 0;
}