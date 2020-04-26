#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct node
{
	int num;
	int level;
	int nodes;
	int correct;
	struct node* left;
	struct node* right;
}Node;

void print(Node* root, int level);

void establish_level(Node* root, int level);

Node* add(Node* root, int a);

// FOR TASK 1
void find_the_correct_nodes(Node* root);

void find_the_full_tree(Node* root, int* tree_size, int* max_tree_size, int* tree_values, int* max_tree_values);

Node* create_the_full_tree(Node* root, int* max_tree_size, int* max_tree_values);


// FOR TASK 2
void find_paths(Node* root, int* path, int* max_path, int* path_values, int* max_path_values);


// FOR TASK 3
void cointing_nodes(Node* root);

void find_the_lowest_suitable_tree(Node* root, int* tree_size, int* current_min_size, int* tree_values);

Node* create_the_lowest_suitable_tree(Node* root, int* tree_size, int* tree_values);

#endif