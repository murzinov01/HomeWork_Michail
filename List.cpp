#include "List.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void add2list(NODE** pphead, int val) {
	NODE** pp = pphead, *pnew;
	while (*pp) {
		pp = &((*pp)->pnext);
	}
	pnew = (NODE*)malloc(sizeof(NODE));
	pnew->value = val;
	pnew->pnext = *pp;
	*pp = pnew;
}

void add2charlist(NODE_CHAR** pphead, char* val) {
	NODE_CHAR** pp = pphead, *pnew;
	while (*pp) {
		pp = &((*pp)->pnext);
	}
	pnew = (NODE_CHAR*)malloc(sizeof(NODE_CHAR));
	pnew->value = (char*)malloc(sizeof(char));
	strcpy(pnew->value, val);
	pnew->pnext = *pp;
	*pp = pnew;
}

void print(NODE* phead) {
	NODE* p = phead;
	while (p) {
		printf("%d ", p->value);
		p = p->pnext;
	}
	printf("\n");
}

void print_char_list(NODE_CHAR* phead){
	NODE_CHAR* p = phead;
	while (p) {
		printf("%s\n", p->value);
		p = p->pnext;
	}
}

void find2equal(NODE* phead) {
	NODE* p = phead;
	int flag = 0;
	while (p) {
		NODE* pnew = p->pnext;
		while (pnew) {
			if (p->value == pnew->value)
				flag = 1;
			pnew = pnew->pnext;
		}
		p = p->pnext;
	}
	printf("There %s two equal numbers", flag ? "are" : "aren't");
}

void createL3(NODE* L1, NODE* L2, NODE** L3) {
	NODE* p1 = L1;
	int flag = 1;
	while (p1) {
		NODE* p2 = L2;
		while (p2) {
			if (p1->value == p2->value)
				flag = 0;
			p2 = p2->pnext;
		}
		if (flag)
			add2list(&*L3, p1->value);
		p1 = p1->pnext;
		flag = 1;
	}
}

void involvelist(NODE_CHAR* L1, NODE_CHAR* L2){
	int size_of_list = 0, flag = 0;
	int poses[5] = { 0 };
	while (L1) {
		NODE_CHAR* p2 = L2;
		int pos = 0;
		while (p2) {
			if (!strcmp(L1->value, p2->value) && !poses[pos]) {
				flag += 1;
				poses[pos++] = 1;
				break;
			}
			p2 = p2->pnext;
			pos++;
		}
		size_of_list += 1;
		L1 = L1->pnext;
	}
	printf("The first list %s in the second list", size_of_list == flag ? "is" : "isn't");
}

void devide_list(NODE_CHAR* L1, NODE_CHAR** L2, NODE_CHAR** L3){
	while (L1) {
		if (int(L1->value[0]) >= 48 && int(L1->value[0]) <= 57)
			add2charlist(&*L2, L1->value);
		else
			add2charlist(&*L3, L1->value);
		L1 = L1->pnext;
	}
}
