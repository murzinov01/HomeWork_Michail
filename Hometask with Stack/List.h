#ifndef LIST_H
#define LIST_H

typedef struct node_char {
	char* value;
	struct node_char* pnext;
}NODE_CHAR;

void add2charlist(NODE_CHAR** pphead, char* val);
void print_char_list(NODE_CHAR* phead);
#endif