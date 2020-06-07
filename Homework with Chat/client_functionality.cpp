#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "client_functionality.h"

#define COMMANDS_NUM 5


void print_dialog_interface(char users[1024]) {
    printf("%s\n", "========================================");
    printf("%s\n", "-------------     CHAT   ---------------");
    printf("%s\n", "=== Users: =============================");
    printf("%s\n", users);
    printf("%s\n", "========================================");
}

RESPONSE response_definer(char* string) {
    RESPONSE my_response;
    char num[10] = { '\0' };
    sscanf(string, "%s %1024[^\n]", num, my_response.message);
    my_response.resp = atoi(num);
    return my_response;
}