#ifndef TREE_H
#define TREE_H

typedef struct Node
{
	char* data;
	struct Node* child;
	struct Node* brother;
}NODE;

NODE* Create(char* s);
NODE* AddBrother(NODE* oldbrother, char* s);
NODE* AddChild(NODE* par, char* s);
void Print(NODE* root, int level, FILE* fout);
NODE* DelTree(NODE* root);


#endif // !TREE_H