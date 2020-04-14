#include "tree.h"
#include <string.h>
#define SIZE 40

Node* nodes_with_signes[SIZE];
int nodes_number = 0, result = 0;

enum TYPE{
    SIGN = 1,
    NUMBER,
    FULL,
};

void check_nodes_with_signes() {
    for (int i = 0; i < nodes_number; i++)
        if (nodes_with_signes[i]->right && nodes_with_signes[i]->left && (!(nodes_with_signes[i]->right->is_signe) && !(nodes_with_signes[i]->left->is_signe)))
            nodes_with_signes[i]->full = FULL;
}

Node* add(Node* root, char* a, int type)
{
    if (!root)
    {
        if (type == SIGN) {
            Node* pnew = (Node*)malloc(sizeof(Node));
            pnew->is_signe = 1;
            pnew->op = *a;
            pnew->left = NULL;
            pnew->right = NULL;
            root = pnew;
            nodes_with_signes[nodes_number++] = root;
        }
        else if (type == NUMBER) {
            Node* pnew = (Node*)malloc(sizeof(Node));
            pnew->is_signe = 0;
            pnew->num = atoi(a);
            pnew->left = NULL;
            pnew->right = NULL;
            root = pnew;
        }
    }
    //if it's a sign
    else if (type == SIGN) {
        if ((!root->left) || root->left->full != FULL)
            root->left = add(root->left, a, type);
        else
            root->right = add(root->right, a, type);
    }
    //If it's a number
    else {
        if (root->left == NULL) {
            if (root->right == NULL) {
                root->right = add(root->right, a, type);
            }
            else {
                root->left = add(root->left, a, type);
            }
        }
        else {
            if (root->left->full != FULL)
                root->left = add(root->left, a, type);
            else
                root->right = add(root->right, a, type);
        }
    }
    check_nodes_with_signes();
    return root;
}

int calculate_expression(int num1, int num2, char sign) {
    switch (sign)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    }
}

int calculate_tree(Node* root) {
    for (int i = nodes_number - 1; i >= 1 ; i--)
        nodes_with_signes[i]->num = calculate_expression(nodes_with_signes[i]->left->num, nodes_with_signes[i]->right->num, nodes_with_signes[i]->op);
    result = calculate_expression(nodes_with_signes[0]->left->num, nodes_with_signes[0]->right->num, nodes_with_signes[0]->op);
    return result;
}

void print(Node* root, int level)
{
    if (root)
        print(root->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("   ");
    if (root) {
        if (root->is_signe) 
            printf("%c   %d\n", root->op, level);
        else
            printf("%d   %d\n", root->num, level);
    }
    else
        printf("#\n");
    if (root)
        print(root->left, level + 1);
}