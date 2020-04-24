#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <io.h>
#include "tree.h"
#include "catalog.h"

enum CONDITION
{
	NOT_FOUND_THE_TARGET_FILE = 0,
	FOUND_THE_TARGET_FILE = 1,
};

int FLAG = 0;
char catalog[100] = { '\0' };

NODE* Go(char* path, NODE* root)
{
	struct _finddata_t fc;
	intptr_t  hFile = _findfirst(path, &fc);
	if (!hFile)
		return root;
	_findnext(hFile, &fc);
	while (_findnext(hFile, &fc) == 0)
	{
		if (fc.attrib & _A_SUBDIR)
		{
			root = AddChild(root, fc.name);
			char path1[1000];
			strcpy(path1, path);
			strcpy(path1 + strlen(path1) - 1, fc.name);
			strcat(path1, "\\*");
			NODE* p = root->child;
			while (p->brother)
				p = p->brother;
			p = Go(path1, p);
		}
		else
			root = AddChild(root, fc.name);
	}
	return root;
}

NODE* MakeTree(char* path, NODE* root)
{
	strcat(path, "\\*");
	root = Go(path, root);
	return root;
}

void FindCatalogs(NODE* root, int level, FILE* fout, char* target_file)
{
	NODE* p = root;
	if (!strstr(p->data, ".")) {
		strcpy(catalog, p->data);
		FLAG = NOT_FOUND_THE_TARGET_FILE;
	}
	if (!strcmp(p->data, target_file) && !FLAG) {
		if (strlen(catalog) > 0)
		{
			fprintf(fout, "%s\n", catalog);
			for (int i = 0; i < level; i++)
				fprintf(fout, "   ");
		}
		FLAG = FOUND_THE_TARGET_FILE;
	}
	if (p->child)
		FindCatalogs(p->child, level + 1, fout, target_file);
	if (p->brother)
		FindCatalogs(p->brother, level, fout, target_file);
}

void NumberOfFilesInDirectory(NODE* root, int* number)
{
	NODE* p = root;
	if (strstr(p->data, "."))
		(*number)++;
	if (p->child)
		NumberOfFilesInDirectory(p->child, number);
	if (p->brother)
		NumberOfFilesInDirectory(p->brother, number);
}

Node* Find(char* path, FILE* fout, unsigned long int* size, Node* root)
{
	struct _finddata_t fc;
	intptr_t  hFile = _findfirst(path, &fc);
	if (!hFile)
		return root;
	_findnext(hFile, &fc);
	while (_findnext(hFile, &fc) == 0)
	{
		if (fc.attrib & _A_SUBDIR)
		{
			root = AddChild(root, fc.name);
			char path1[1000];
			strcpy(path1, path);
			strcpy(path1 + strlen(path1) - 1, fc.name);
			strcat(path1, "\\*");
			NODE* p = root->child;
			while (p->brother)
				p = p->brother;
			p = Find(path1, fout, size, p);
		}
		else {
			root = AddChild(root, fc.name);
			if (fc.size > *size)
				fprintf(fout, "%s\n", fc.name);
		}
	}
	return root;
}

void FindTheHugeFiles(NODE* root, FILE* fout, char* path, unsigned long int* size)
{
	strcat(path, "\\*");
	root = Find(path, fout, size, root);
	DelTree(root);
}