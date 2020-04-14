#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#include "tree.h"

#define SIZE 40

int find_value(char variable, char variables[SIZE + 1], int variable_size) {
	for (int i = 0; i < variable_size; i++) {
		if (variables[i] == variable)
			return i;
	}
	return -1;
}

void get_expression_in_numbers(char expression[]) {
	char variables[SIZE + 1] = { '\0' };
	char values[SIZE + 1][10] = { '\0' };
	char new_expression[SIZE + 1] = { '\0' };
	int variables_size = 0;
	int len_of_new_expression = 0;
	for (int i = 0; i < strlen(expression); i++) {
		if ((int(expression[i]) >= 65 && int(expression[i]) <= 90 || int(expression[i]) >= 97 && int(expression[i]) <= 122) && (find_value(expression[i], variables, variables_size) == -1)) {
			variables[variables_size++] = expression[i];
		}
	}
	printf("Enter the values:\n");
	for (int j = 0; j < variables_size; j++) {
		printf("%c = ", variables[j]);
		gets_s(values[j], 10);
	}
	for (int i = 0; i < strlen(expression); i++) {
		if (int(expression[i]) >= 65 && int(expression[i]) <= 90 || int(expression[i]) >= 97 && int(expression[i]) <= 122) {
			char* value = values[find_value(expression[i], variables, variables_size)];
			for (int j = 0; j < strlen(value); j++)
				new_expression[len_of_new_expression++] = value[j];
		}
		else
			new_expression[len_of_new_expression++] = expression[i];
	}
	for (int i = 0; i < len_of_new_expression; i++)
		expression[i] = new_expression[i];
	expression[len_of_new_expression] = '\0';
}

int main() {
	enum TYPE {
		SIGN = 1,
		NUMBER,
	};
	STACK* RPN = NULL;
	Node* root = NULL;
	Node* start_root = NULL;
	char expression[SIZE + 1] = { '\0' };

	printf("Input the expression > ");
	gets_s(expression, SIZE);

	//filling out the expression with numbers
	get_expression_in_numbers(expression);
	printf("Initial expression: %s\n", expression);

	//Getting Reverse Polish Notation
	RPN = get_RPN(RPN, expression);
	
	//creating the tree
	char element[SIZE + 1] = { '\0' };
	strcpy(element, top(RPN));
	start_root = add(root, element, SIGN);
	root = start_root;
	RPN = pop(RPN);
	while (!isEmpty(RPN)){
		char element[SIZE + 1] = { '\0' };
		strcpy(element, top(RPN));
		if ((*top(RPN)) >= 48 && (*top(RPN)) <= 57) {
			root = add(start_root, element, NUMBER);
		}
		else
			root = add(start_root, element, SIGN);
		RPN = pop(RPN);
	}

	//print the tree
	printf("Tree:\n");
	print(start_root, 0);
	printf("Result: %d", calculate_tree(start_root));
	return 0;
}