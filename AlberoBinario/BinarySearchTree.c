#include "./BinarySearchTree.h"

/**
 * @brief Create a node object
 * 
 * @param value 
 * @return treeNode* 
 */
treeNode* create_node(int value){
    treeNode* node=(treeNode*)malloc(sizeof(treeNode));
    node->data=value;
    node->left=NULL;
    node->right=NULL;
    return node;
}

/**
 * @brief insert node in the tree
 * 
 * @param bst ...pointer to bst pointer
 * @param value 
 */
void insert_node(treeNode** bst, int value){
    treeNode* node=create_node(value);
    if((*bst)==NULL){
        (*bst)=node;
    }
    else{
        insert_node_recursive((*bst), node);
    }
}

void insert_node_recursive(treeNode* bst, treeNode* node){
    if(node->data == bst->data){
        printf("Node already exists in the tree.\n");
        return;
    }
    if(node->data < bst->data){
        if(bst->left==NULL){
            bst->left=node;
        }
        else{
            insert_node_recursive(bst->left,node);
        }
    }
    if(node->data > bst->data){
        if(bst->right==NULL){
            bst->right=node;
        }
        else{
            insert_node_recursive(bst->right,node);
        }
    }
}

int main(){}