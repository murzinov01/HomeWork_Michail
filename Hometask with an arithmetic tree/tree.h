#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 40

typedef struct node
{
	int full = 0;
	int num;
	int is_signe = 0;
	char op = '\0';
	struct node* left;
	struct node* right;
}Node;

Node* add(Node* root, char* a, int type);

void print(Node* root, int level);

int calculate_tree(Node* root);

#endif