#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")
#include <winsock.h>

enum states {
	NEW_MESSAGE = 1,
	NEED_AUTH,
	USER_NOT_FOUND,
	COMMAND_MISTAKE,
	COMMAND_HELP,
	COMMAND_REG_SUC,
	COMMAND_REG_MIS,
	LOGGED,
	REGISTRED,
	INVALID_CHAT,
	VALID_CHAT,
	START_HISTORY,
	END_HISTORY,
};

enum commands {
	MISTAKE = 0,
	HELP,
	REG,
	LOGIN,
	CHAT,
	CHAT_EXIT,
	MESSAGE,
	EXIT_CHAT,
};

typedef struct command {
    int command_num;
    int args_num;
    char args[10][50];
    char message[1024];
}COMMAND;

typedef struct chat_params {
	int chat_id;
	int user_id;
	SOCKET client_;
}CHAT_PARAMS;

typedef struct responce {
    int resp;
    char message[1024];
}RESPONCE;

COMMAND command_definer(char* string);

int reg_user(char* login, char* password);

void clear_data();

int read_all_users();

int read_all_chats();

int check_users(char* user);

int check_password(char* user, char* password);

int check_valid_chat(char args[10][50], int users_num);

int create_chat(char args [10][50], int users_num);

int find_chat(char args[10][50], int users_num);

char* find_user_by_id(int id);

int find_id_by_user(char* user);

void set_online_status(int id, int status);

int count_online(int chat_id);


#endif // !"FUNCTIONALITY_H"
