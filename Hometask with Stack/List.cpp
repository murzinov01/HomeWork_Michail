#include "List.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void add2charlist(NODE_CHAR** pphead, char* val) {
	NODE_CHAR** pp = pphead, * pnew;
	while (*pp) {
		pp = &((*pp)->pnext);
	}
	pnew = (NODE_CHAR*)malloc(sizeof(NODE_CHAR));
	pnew->value = (char*)malloc(sizeof(char));
	strcpy(pnew->value, val);
	pnew->pnext = *pp;
	*pp = pnew;
}

void print_char_list(NODE_CHAR* phead) {
	NODE_CHAR* p = phead;
	while (p) {
		printf("%s\n", p->value);
		p = p->pnext;
	}
}
