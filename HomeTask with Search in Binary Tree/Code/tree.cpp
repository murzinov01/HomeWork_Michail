#include "tree.h"

#define MAX_SIZE 100

enum status {
    UNCORRECT = 0,
    CORRECT,
};

int TARGET_LEVEL = MAX_SIZE;

Node* add(Node* root, int a)
{
    if (!root)
    {
        Node* pnew = (Node*)malloc(sizeof(Node));
        pnew->num = a;
        pnew->correct = 0;
        pnew->nodes = 0;
        pnew->left = NULL;
        pnew->right = NULL;
        root = pnew;
    }
    else if (root->num < a)
        root->right = add(root->right, a);
    else
        root->left = add(root->left, a);
    return root;
}

void print(Node* root, int level)
{
    if (root)
        print(root->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("   ");
    if (root)
        printf("%d   %d\n", root->num, level);
    else
        printf("#\n");
    if (root)
        print(root->left, level + 1);
}

// FOR TASK 1

// Looking for suitable nodes for the full tree
void find_the_correct_nodes(Node* root)
{
    if (root)
    {
        find_the_correct_nodes(root->left);
        find_the_correct_nodes(root->right);
        // If the node has no children, or both are present
        if ((root->left && root->right) || (!(root->left && !root->right)))
            root->correct = CORRECT;

        // If the left node carries the wrong tree under it
        if (root->left) 
            if (root->left->correct == UNCORRECT) 
                root->correct = UNCORRECT;

        // If the right node carries the wrong tree under it
        if (root->right) 
            if (root->right->correct == UNCORRECT) 
                root->correct = UNCORRECT;
    }
}

// Using suitable nodes, we find the nodes of the largest complete tree
void find_the_full_tree(Node* root, int* tree_size, int* max_tree_size, int* tree_values, int* max_tree_values)
{
    if (root)
    {
        find_the_full_tree(root->left, tree_size, max_tree_size, tree_values, max_tree_values);
        find_the_full_tree(root->right, tree_size, max_tree_size, tree_values, max_tree_values);

        // If you find a node in the correct tree
        if (root->correct == CORRECT)
            tree_values[(*tree_size)++] = root->num;

        // Getting out of the correct tree and saving it
        else if (root->correct == UNCORRECT)
        {
            if (*max_tree_size < *tree_size)
            {
                *max_tree_size = *tree_size;
                for (int i = 0; i < *max_tree_size; i++)
                    max_tree_values[i] = tree_values[i];
            }
            *tree_size = 0;
        }
    }
}

// Using these nodes we build a tree
Node* create_the_full_tree(Node* root, int* tree_size, int* tree_values)
{
    for (int i = *tree_size - 1; i >= 0; i--)
        root = add(root, tree_values[i]);
    return root;
}


// FOR TASK 2
void find_paths(Node* root, int* path, int* max_path, int* path_values, int* max_path_values)
{
    if (root)
    {
        // If one child
        if (!(root->left) && root->right || root->left && !(root->right))
            path_values[(*path)++] = root->num;
        // If you hit a leaf (the node has no children)
        if (!root->left && !root->right)
        {
            path_values[*path] = root->num;
            if (*max_path < *path)
            {
                *max_path = *path;
                for (int i = 0; i <= *max_path; i++)
                    max_path_values[i] = path_values[i];
            }
            *path = 0;
        }
        // If you hit a fork
        else if (root->left && root->right && *path > 0)
        {
            if (*max_path < *path)
            {
                *max_path = *path;
                for (int i = 0; i < *max_path; i++)
                    max_path_values[i] = path_values[i];
            }
            *path = 0;
        }
        find_paths(root->left, path, max_path, path_values, max_path_values);
        find_paths(root->right, path, max_path, path_values, max_path_values);
    }
}


// FOR TASK 3

void establish_level(Node* root, int level)
{
    if (root)
    {
        root->level = level;
        if (root->left || root->right)
            level++;
        establish_level(root->left, level);
        establish_level(root->right, level);
    }
}

void cointing_nodes(Node* root)
{
    if (root)
    {
        cointing_nodes(root->left);
        cointing_nodes(root->right);

        // Consider children of a node
        if (!root->right && !root->left)
            root->nodes++;
        else if (root->right && root->left)
            root->nodes = root->right->nodes + root->left->nodes + 1;
        else if (root->right)
            root->nodes = root->right->nodes + 1;
        else if (root->left)
            root->nodes = root->left->nodes + 1;
    }
}

void find_the_lowest_suitable_tree(Node* root, int* tree_size, int* current_min_size, int* tree_values)
{
    if (root)
    {
        // Found the root of a suitable tree
        if (root->nodes == root->num && root->num < *current_min_size)
        {
            *current_min_size = root->num;
            *tree_size = 0;
            TARGET_LEVEL = root->level;
            tree_values[(*tree_size)++] = root->num;
        }
        else
        {   
            // Adding nodes to the appropriate tree
            if (root->level > TARGET_LEVEL) {
                tree_values[(*tree_size)++] = root->num;
            }
            // Comming out of a suitable tree
            else
                TARGET_LEVEL = MAX_SIZE;
        }
        find_the_lowest_suitable_tree(root->left, tree_size, current_min_size, tree_values);
        find_the_lowest_suitable_tree(root->right, tree_size, current_min_size, tree_values);
    }
}

Node* create_the_lowest_suitable_tree(Node* root, int* tree_size, int* tree_values)
{
    for (int i = 0; i < *tree_size; i++)
        root = add(root, tree_values[i]);
    return root;
}