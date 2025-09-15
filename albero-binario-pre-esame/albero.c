#include "albero.h"
#include <queue.h>
/**
 * @brief inizializza l'albero
 * 
 * @param root 
 */
void init(treeNode* root){
    treeNode* newNode=(treeNode*)malloc(sizeof(treeNode));
    newNode->val=0;
    newNode->left=NULL;
    newNode->right=NULL;
}

/**
 * @brief controlla se l'albero è vuoto
 * 
 * @param root 
 * @return true 
 * @return false 
 */
bool isEmpty(treeNode* root){
    if(root==NULL) return true;
    return false;
}


int main(){}