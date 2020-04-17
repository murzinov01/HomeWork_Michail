#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "catalog.h"

#define MAX_FILE_SIZE 100
#define MAX_PATH_SIZE 1000

int main(int  argc, char* argv[])
{
	if (argc < 3)
		return -1;

	FILE* fout;
	FILE* found_catalogs;
	FILE* huge_files;
	NODE* root = NULL;
	char path[MAX_PATH_SIZE];
	//Open the files
	fout = fopen(argv[1], "w");
	found_catalogs = fopen(argv[2], "w");
	huge_files = fopen(argv[3], "w");
	if (!fout || !found_catalogs || !huge_files)
	{
		printf("Error opening the file");
		return -1;
	}
	strcpy(path, argv[4]);
	root = Create(path);
	root = MakeTree(path, root);
	Print(root, 0, fout);

						// TASK 1
	/*char target_file[MAX_FILE_SIZE] = { '\0' };
	printf("Enter the target file > ");
	gets_s(target_file, MAX_FILE_SIZE);
	FindCatalogs(root->child, 0, found_catalogs, target_file);*/

						// TASK 2
	/*int number_of_files_in_directory = 0;
	NumberOfFilesInDirectory(root, &number_of_files_in_directory);
	printf("Number of files in this directory is %d", number_of_files_in_directory);*/
						// TASK 3
	char directory_path[MAX_PATH_SIZE];
	int size = 0;
	Node* new_root = NULL;
	printf("Enter the size of file in bytes > ");
	scanf_s("%d", &size);
	strcpy(directory_path, argv[4]);
	new_root = Create(directory_path);
	FindTheHugeFiles(new_root, huge_files, directory_path, &size);

	//Close the files and delete tree
	fclose(fout);
	fclose(found_catalogs);
	fclose(huge_files);
	root = DelTree(root);
	return 0;
}
