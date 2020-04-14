#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Stack.h"

#define SIZE 40

STACK* push(STACK* head, char* val) {
	STACK* temp = (STACK*)malloc(sizeof(STACK));
	temp->data = (char*)malloc((strlen(val) + 1) * sizeof(char));
	strcpy(temp->data, val);
	temp->next = head;
	return temp;
}

STACK* pop(STACK* head) {
	if (head)
	{
		STACK* temp = head->next;
		free(head->data);
		free(head);
		return temp;
	}
}

char* top(STACK* head) {
	return head->data;
}

int isEmpty(STACK* head) {
	return head ? 0 : 1;
}

int get_number_and_its_size(char num[], char str[], int i) {
	int num_size = 0;
	while ((i != strlen(str)) && (int(str[i]) > 47 && int(str[i]) < 58)) {
		num[num_size++] = str[i++];
	}
	return num_size;
}

int set_priority(char ch) {
	if (ch == '+' || ch == '-') return 1;
	else if (ch == '*' || ch == '/') return 2;
	else return -1;
}

STACK* get_RPN(STACK* RPN, char expression[]) {
	STACK* operands = NULL;
	int i = 0, rpn_size = 0, op_size = 0;
	while (i != strlen(expression)) {
		//Если это число, то добавляем его в стэк RPN
		if (expression[i] > 47 && expression[i] < 58) {;
			char num[SIZE + 1] = { '\0' };
			int num_size = get_number_and_its_size(num, expression, i);
			RPN = push(RPN, num);
			i += num_size;
			rpn_size += num_size;
		}
		// Если это знак операции
		else if (int(expression[i]) != 40 && int(expression[i]) != 41) {
			// если стэк операции пуст или в нем скобка
			if (op_size == 0 || *(top(operands)) == '(') { 
				char sign[2] = { '\0' };
				*sign = expression[i++];
				operands = push(operands, sign);
				op_size++;
			}
			//Если приоритет операции больше, чем приоритет операции в стэке
			else if (set_priority(expression[i]) > set_priority(*top(operands))) {
				char sign[2] = { '\0' };
				*sign = expression[i++];
				operands = push(operands, sign);
				op_size++;
			}
			//Если приоритет операции меньше, чем приоритет операции в стэке
			else {
				while (op_size > 0 && set_priority(expression[i]) <= set_priority(*top(operands))) {
					char operand[2] = { '\0' };
					*operand = *top(operands);
					RPN = push(RPN, operand);
					operands = pop(operands);
					rpn_size++;
					op_size--;
				}
				char operand[2] = { '\0' };
				*operand = expression[i];
				operands = push(operands, operand);
  				op_size++;
				i++;
			}
		}
		//Если открывающаяся скобочка
		else if (int(expression[i]) == 40) {;
			//printf("***\n");
			char bracket[2] = { '\0' };
			*bracket = expression[i++];
			operands = push(operands, bracket);
			op_size++;
		}
		//Если закрывающаяся скобочка
		else if (int(expression[i]) == 41) {;
			char operand[2] = { '\0' };
			*operand = *top(operands);
			//printf("%s", operand);
			//printf("****\n");
			while (int((*operand)) != 40) {
				RPN = push(RPN, operand);
				rpn_size++;
				operands = pop(operands);
				*operand = *top(operands);
				op_size--;
			}
			operands = pop(operands);
			op_size--;
			i++;
		}
	}
	//Когда строка закончилась
	while (op_size != 0) {
		char operand[2] = { '\0' };
		*operand = *top(operands);
		RPN = push(RPN, operand);
		operands = pop(operands);
		op_size--;
		rpn_size++;
	}
	return RPN;
}