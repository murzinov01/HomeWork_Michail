#include<windows.h>
#include<stdio.h>
#include "tree.h"

#define CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 100

int main()
{	// initialization of the tree
	Node* root = NULL;
	int start_level = 0;
	srand(time(0));
	for (int i = 0; i < 8; i++) {
		int a = rand() % 101 - 50;
		root = add(root, a);
	}
	//				Task 1
	/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 9 % 15);
	printf("INITIAL TREE: \n");
	SetConsoleTextAttribute(hConsole, 14 % 15);
	print(root, 0);

	int tree_size = 0, max_tree_size = 0;
	int tree_values[MAX_SIZE] = { 0 };
	int max_tree_values[MAX_SIZE] = { 0 };
	Node* full_tree = NULL;
	find_the_correct_nodes(root);
	find_the_full_tree(root, &tree_size, &max_tree_size, tree_values, max_tree_values);
	full_tree = create_the_full_tree(full_tree, &max_tree_size, max_tree_values);

	SetConsoleTextAttribute(hConsole, 9 % 15);
	printf("THE MAX FULL TREE: \n");
	SetConsoleTextAttribute(hConsole, 10 % 15);
	print(full_tree, 0);*/

	//				TASK 2
	/*print(root, 0);
	int path = 0, max_path = 0;
	int path_values[MAX_SIZE] = { 0 };
	int max_path_values[MAX_SIZE] = { 0 };
	find_paths(root, &path, &max_path, path_values, max_path_values);
	printf("\nThe maximum path of the tree is : %d", max_path + 1);
	printf("\nPath: ");
	for (int i = 0; i < max_path; i++)
		printf("%d => ", max_path_values[i]);
	printf("%d", max_path_values[max_path]);*/

	//				TASK 3
	// initialization of the tree
	/*int level = 0, tree_size = 0, current_min_size = MAX_SIZE;
	int tree_values[MAX_SIZE] = { 0 };
	Node* new_root = NULL;
	Node* the_lowest_suitable_tree = NULL;
	int example[7] = { 21, 5, 3, 7, 2, 4, 41 };
	for (int i = 0; i < 7; i++) {
		new_root = add(new_root, example[i]);
	}

	// print initial tree
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 9 % 15);
	printf("INITIAL TREE: \n");
	SetConsoleTextAttribute(hConsole, 14 % 15);
	print(new_root, 0);

	establish_level(new_root, level);
	cointing_nodes(new_root);
	find_the_lowest_suitable_tree(new_root, &tree_size, &current_min_size, tree_values);
	the_lowest_suitable_tree = create_the_lowest_suitable_tree(the_lowest_suitable_tree, &tree_size, tree_values);
	
	//print the answer
	SetConsoleTextAttribute(hConsole, 9 % 15);
	printf("THE LOWEST SUITABLE TREE: \n");
	SetConsoleTextAttribute(hConsole, 10 % 15);
	print(the_lowest_suitable_tree, 0);*/

	return 0;
}
