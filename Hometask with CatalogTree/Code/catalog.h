#ifndef CATALOG_H
#define CATALOG_H

#define MAX_SIZE 10

NODE* MakeTree(char* path, NODE* root);

Node* Find(char* path, FILE* fout, unsigned long int* size, Node* root);

void FindCatalogs(NODE* root, int level, FILE* fout, char* target_file);

void NumberOfFilesInDirectory(NODE* root, int* number);

void FindTheHugeFiles(NODE* root, FILE* fout, char* path, unsigned long int* size);

#endif // !CATALOG_H

