#ifndef LIST_BST_H
#define LIST_BST_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
typedef struct ListNode{
    int data;
    struct ListNode* next;
}ListNode;
typedef struct BstNode{
    int data;
    struct BstNode* left;
    struct BstNode* right;
}BstNode;
ListNode* readList();
void addListNode(ListNode* head, int val);
BstNode* ListToBst(ListNode* head);
#endif