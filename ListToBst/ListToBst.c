#include "ListToBst.h"
/**
 * @brief aggiunge un nodod in coda
 *
 * 
 * @param head 
 * @param value 
 */
void addTail(ListNode* head, int value){
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    ListNode* current = head;
    while(current->next != NULL){
        current=current->next;
    }
    newNode->data=value;
    newNode->next=NULL;
    current->next=newNode;
}
/**
 * @brief stampa la lista
 * 
 * @param head 
 */
void printList(ListNode* head){
    ListNode* current = head;
    while(current!=NULL){
        printf("%d ",current->data);
        current=current->next;
    } 
}
/**
 * @brief creiamo una lista con i nostri valori
 * 
 * @return ListNode* 
 */
ListNode* readList(){
    FILE* f=fopen("list.txt", "r");
    if(f==NULL){
        printf("Error opening file");
        return NULL;
    }
    int c = fgetc(f);
    if (c == EOF) {
        return NULL;
    }
    ungetc(c, f);
    ListNode* head=(ListNode*)malloc(sizeof(ListNode));
    int n;
    char s[256];
    fgets(s,sizeof(s),f);
    n=atoi(s);
    head->data=n;
    head->next=NULL;
    while(fgets(s,sizeof(s),f)){
        addTail(head, atoi(s));
    }
    fclose(f);
    return head;
}

BstNode* GenerateBst(ListNode* head){
    BstNode* root = (BstNode*)malloc(sizeof(BstNode));
    root->data=head->data;
    root->left=NULL;
    root->right=NULL;
    while(head->next!=NULL){
        addBstNode(root,head->data);
    }
    return root;
}

/**
 * @brief Main
 * 
 * @return int 
 */
int main(){
    ListNode* head= readList();
    printList(head);
    BstNode* BST = GenerateBst(head);
}