#ifndef LIST_H
#define LIST_H

typedef struct node {
	int value;
	struct node* pnext;
}NODE;

typedef struct node_char {
	char* value;
	struct node_char* pnext;
}NODE_CHAR;

void add2list(NODE** pphead, int val);
void add2charlist(NODE_CHAR** pphead, char* val);
void print(NODE* phead);
void print_char_list(NODE_CHAR* phead);
void find2equal(NODE* phead);
void createL3(NODE* L1, NODE* L2, NODE** L3);
void involvelist(NODE_CHAR* L1, NODE_CHAR* L2);
void devide_list(NODE_CHAR* L1, NODE_CHAR** L2, NODE_CHAR** L3);
#endif