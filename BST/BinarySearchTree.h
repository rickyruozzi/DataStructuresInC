#ifndef BINARYSEARCHTREE 
#define BINARYSEARCHTREE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct treeNode{
    int data;
    struct treeNode* left;
    struct treeNode* right;
}treeNode;
treeNode* create_node(int value);
void insert_node(treeNode** bst, int value);
void insert_node_recursive(treeNode* bst, treeNode* node);
bool find_node(treeNode* bst, int value);
void print_pre_order(treeNode* bst);
void print_post_order(treeNode* bst);
bool stampa_antenati(treeNode* bst, int value);
#endif