#ifndef STACK_H
#define STACK_H
#include "List.h"
//stack functions
void push(char* val);
void pop();
char* top();
int isEmpty();
//For TASK 1
void print_reverse_string_in_stack_stack();
//FOR TASK 2
void check_polindrom(char string[]);
//FOR TASK 3
void create_reverse_copy_list(NODE_CHAR** Copy_List);
//FOR TASK 4
void write_reverse_strings_in_file();
//FOR TASK 5
void brackets(char buffer[]);
#endif
