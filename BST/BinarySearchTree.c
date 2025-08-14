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

/**
 * @brief return true if a specified value has been found in the bst 
 * 
 * @param bst 
 * @param value 
 * @return true 
 * @return false 
 */
bool find_node(treeNode* bst, int value){
    if(bst == NULL){
        return false;
    }
    if(bst->data==value){
        return true;
    }
    if(value < bst->data){
        return find_node(bst->left, value);
    }
    if(value > bst->data){
        return find_node(bst->right, value);
    }
    return false;
}

/**
 * @brief print bst pre_view
 * 
 * @param bst 
 */
void print_pre_order(treeNode* bst){
    if(bst != NULL){
        printf("Il valore del nodo è: %d\n",bst->data);
        print_pre_order(bst->left);
        print_pre_order(bst->right);
    }
}


/**
 * @brief print bst post_view
 * 
 * @param bst 
 */
void print_post_order(treeNode* bst){
    if(bst != NULL){
        print_post_order(bst->left);
        print_post_order(bst->right);
        printf("Il valore del nodo è: %d\n ",bst->data);
    }
}

int main(){}