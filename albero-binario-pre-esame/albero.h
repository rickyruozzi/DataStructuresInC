#ifndef ABPE
#define ABPE
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>
typedef struct treeNode{
    int val;
    struct treeNode* left;
    struct treeNode* right;
}treeNode;

void init(treeNode* root);
bool isEmpty(treeNode* root);
void insert(treeNode* root, int val); // inserimento per livello
bool search(treeNode* root, int val);
void printInOrder(treeNode* root);
void printPreOrder(treeNode* root);
void printPostOrder(treeNode* root);
void freeTree(treeNode* root);
#endif