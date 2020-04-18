#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#include "List.h"

#define SIZE 20

//							TASK 1
/*int main()
{
	char string[SIZE + 1] = { '\0' };
	gets_s(string, SIZE);
	for (int i = 0; string[i]; i++)
		push(&string[i]);
	print_reverse_string_in_stack_stack();
	return 0;
}*/
//							TASK 2
/*int main() {
	char string[SIZE + 1] = { '\0' };
	gets_s(string, SIZE);
	for (int i = 0; string[i]; i++)
		push(&string[i]);
	check_polindrom(string);
	return 0;
}*/
//							TASK 3
/*int main() {
	char* symbol;
	symbol = (char*)malloc(2* sizeof(char));
	NODE_CHAR* List = NULL;
	NODE_CHAR* Copy_List = NULL;
	for (int i = 0; i < 10; i++) {
		gets_s(symbol, 2);
		push(symbol);
		add2charlist(&List, symbol);
	}
	create_reverse_copy_list(&Copy_List);
	printf("The reverse copy list is: \n");
	print_char_list(Copy_List);
	free(symbol);
	return 0;
}*/
//							TASK 4
/*int main() {
	FILE* fr;
	char buffer[SIZE + 1] = { '\0' };
	if ((fr = fopen("strings.txt", "r")) == NULL) {
		printf("Could not open the file");
		return 0;
	}
	while (!feof(fr)) {
		fgets(buffer, SIZE, fr);
		push(buffer);
	}
	write_reverse_strings_in_file();
	fclose(fr);
	return 0;
}*/
//							TASK 5
/*int main() {
	char buffer[SIZE + 1] = { '\0' };
	gets_s(buffer, SIZE);
	brackets(buffer);
}*/