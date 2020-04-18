#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Stack.h"

#define SIZE 20

typedef struct stack{
	char* data;
	struct stack* next;
}STACK;

STACK* head = NULL;

void push(char* val){
	STACK* temp = (STACK*)malloc(sizeof(STACK));
	temp->data = (char*)malloc((strlen(val) + 1) * sizeof(char));
	strcpy(temp->data, val);
	temp->next = head;
	head = temp;
}

void pop(){
	if (head)
	{
		STACK* temp = head->next;
		free(head->data);
		free(head);
		head = temp;
	}
}

char* top(){
	return head->data;
}

int isEmpty(){
	return head ? 0 : 1;
}

void print_reverse_string_in_stack_stack() {
	while (!isEmpty()) {
		printf("%c", *top());
		pop();
	}
}

void check_polindrom(char string[]) {
	char polindrom[SIZE + 1] = { '\0' };
	for (int i = 0; !isEmpty(); i++) {
		polindrom[i] = *top();
		pop();
	}
	printf("Initial string %s polindrom.", !strcmp(string, polindrom) ? "is" : "isn't");
}


void create_reverse_copy_list(NODE_CHAR** Copy_List) {
	while (!isEmpty()) {
		add2charlist(&*Copy_List, top());
		pop();
	}
}

void write_reverse_strings_in_file() {
	FILE* fw;
	if ((fw = fopen("reverse_strings.txt", "w")) == NULL) {
		printf("Could not open the file");
		return;
	}
	pop();
	while (!isEmpty()) {
		fputs(top(), fw);
		pop();
	}
	fclose(fw);
}

char change_the_bracket(char bracket) {
	if (bracket == '(')
		return ')';
	else if (bracket == ')')
		return '(';
	else if (bracket == '[')
		return ']';
	else if (bracket == ']')
		return '[';
	else if (bracket == '{')
		return '}';
	else if (bracket == '}')
		return '{';
	
}

void brackets(char buffer[]) {
	for (int i = 0; buffer[i]; i++) {
		if (isEmpty())
			push(&buffer[i]);
		else if (buffer[i] == change_the_bracket(*top()))
			pop();
		else
			push(&buffer[i]);
	}
	printf("The string %s correct.", isEmpty() ? "is" : "isn't");
}