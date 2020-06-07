#pragma once
#ifndef CLIENT_FUNCTIONALITY
#define CLIENT_FUNCTIONALITY


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

typedef struct command {
    int command_num;
    int args_num;
    char args[10][50];
    char message[1024];
}COMMAND;

typedef struct response {
    int resp;
    char message[1024];
}RESPONSE;

RESPONSE response_definer(char* string);

void print_dialog_interface(char users[1024]);

#endif 