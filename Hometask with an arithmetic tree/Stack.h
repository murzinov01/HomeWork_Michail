#ifndef STACK_H
#define STACK_H

typedef struct stack {
	char* data;
	struct stack* next;
}STACK;

STACK* push(STACK* head, char* val);
STACK* pop(STACK* head);
char* top(STACK* head);
int isEmpty(STACK* head);
STACK* get_RPN(STACK* RPN, char expression[]);
#endif
