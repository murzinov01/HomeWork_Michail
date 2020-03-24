#include "List.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
						//The first task
/*int main()
{
	int number = 0;
	NODE* phead = NULL;
	for (int i = 0; i < 5; i++) {
		scanf_s("%d", &number);
		add2list(&phead, number);
	}
	find2equal(phead);
	return 0;
}*/

						//The second task
/*int main()
{
	int number = 0;
	NODE* L1 = NULL;
	NODE* L2 = NULL;
	NODE* L3 = NULL;
	for (int i = 0; i < 5; i++) {
		scanf_s("%d", &number);
		add2list(&L1, number);
	}
	print(L1);
	for (int i = 0; i < 3; i++) {
		scanf_s("%d", &number);
		add2list(&L2, number);
	}
	print(L2);
	createL3(L1, L2, &L3);
	printf("Result is :\n");
	print(L3);
	return 0;
}*/

					//The third task
/*int main() {
	char* string;
	NODE_CHAR* L1 = NULL;
	NODE_CHAR* L2 = NULL;
	string = (char*)malloc(SIZE * sizeof(char));
	//Entering the first list
	printf("Enter the first list, please: \n");
	for (int i = 0; i < 3; i++) {
		gets_s(string, SIZE);
		add2charlist(&L1, string);
	}
	//Entering the second list
	printf("Enter the second list, please: \n");
	for (int i = 0; i < 5; i++) {
		gets_s(string, SIZE);
		add2charlist(&L2, string);
	}
	involvelist(L1, L2);
	return 0;
}*/
					//The fourth task
/*int main() {
	char* string;
	NODE_CHAR* L1 = NULL;
	NODE_CHAR* NUMBER_CHAR_LIST = NULL;
	NODE_CHAR* CHAR_LIST = NULL;
	string = (char*)malloc(SIZE * sizeof(char));
	//Entering the first list
	printf("Enter the list, please: \n");
	for (int i = 0; i < 6; i++) {
		gets_s(string, SIZE);
		add2charlist(&L1, string);
	}
	devide_list(L1, &NUMBER_CHAR_LIST, &CHAR_LIST);
	printf("The list with number's chars: \n");
	print_char_list(NUMBER_CHAR_LIST);
	printf("The list with chars: \n");
	print_char_list(CHAR_LIST);
	return 0;
}*/