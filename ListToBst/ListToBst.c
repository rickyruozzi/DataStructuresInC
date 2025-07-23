#include <stdio.h>
#include <stdlib.h>
#include "ListToBst.h"

/**
 * @brief Aggiunge un nodo in coda alla lista
 * 
 * @param head 
 * @param value 
 */
void addTail(ListNode* head, int value){
    if (head == NULL) return;
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    ListNode* current = head;
    while(current->next != NULL){
        current = current->next;
    }
    newNode->data = value;
    newNode->next = NULL;
    current->next = newNode;
}

/**
 * @brief stampa la lista
 * 
 * @param head 
 */
void printList(ListNode* head){
    ListNode* current = head;
    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    } 
    printf("\n");
}

/**
 * @brief Crea la lista leggendola da file
 * 
 * @return ListNode* 
 */
ListNode* readList(){
    FILE* f = fopen("list.txt", "r");
    if(f == NULL){
        printf("Error opening file\n");
        return NULL;
    }

    int c = fgetc(f);
    if (c == EOF) {
        fclose(f);
        return NULL;
    }
    ungetc(c, f);

    char s[256];
    if (fgets(s, sizeof(s), f) == NULL) {
        fclose(f);
        return NULL;
    }

    int n = atoi(s);
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    head->data = n;
    head->next = NULL;

    while(fgets(s, sizeof(s), f)){
        addTail(head, atoi(s));
    }

    fclose(f);
    return head;
}

/**
 * @brief aggiunge un nodo al BST
 * 
 * @param root
 * 
 * @param data
 */
void addBstNode(BstNode* root, int data){
    if(data > root->data && root->right == NULL){
        BstNode* nodoBST = (BstNode*)malloc(sizeof(BstNode));
        nodoBST->data = data;
        nodoBST->left = NULL;
        nodoBST->right = NULL;
        root->right = nodoBST;
        return;
    }
    if(data < root->data && root->left == NULL){
        BstNode* nodoBST = (BstNode*)malloc(sizeof(BstNode));
        nodoBST->data = data;
        nodoBST->left = NULL;
        nodoBST->right = NULL;
        root->left = nodoBST;
        return;
    }
    if(data > root->data){
        addBstNode(root->right, data);
    }
    if(data < root->data){
        addBstNode(root->left, data);
    }
}

/**
 * @brief crea il BST
 * 
 * @param head 
 * @return BstNode* 
 */
BstNode* GenerateBst(ListNode* head){
    if (head == NULL) return NULL;
    BstNode* root = (BstNode*)malloc(sizeof(BstNode));
    root->data = head->data;
    root->left = NULL;
    root->right = NULL;
    head = head->next;

    while (head != NULL) {
        addBstNode(root, head->data);
        head = head->next;
    }

    return root;
}

/**
 * @brief libera la memoria della lista
 * 
 * @param head
 */
void freeList(ListNode* head){
    while (head != NULL){
        ListNode* tmp = head;
        head = head->next;
        free(tmp);
    }
}

/**
 * @brief libera la memoria del BST
 * 
 * @param root
 */
void freeBst(BstNode* root){
    if (root == NULL) return;
    freeBst(root->left);
    freeBst(root->right);
    free(root);
}

/**
 * @brief Main
 */
int main(){
    ListNode* head = readList();
    if (head == NULL) return 1;

    printList(head);
    BstNode* BST = GenerateBst(head);

    // Libera la memoria
    freeList(head);
    freeBst(BST);

    return 0;
}
