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
        printf("valore del nodo: %d\n",bst->data);
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
        printf("valore del nodo: %d\n ",bst->data);
    }
}

/**
 * @brief read a BST form a file
 * 
 * @param f 
 * @return treeNode* 
 */
treeNode* readFromFile(FILE* f){
    if (!f){
        perror("Errore nell'apertura del file");
        return NULL;
    }
    int data;
    treeNode* bst=NULL;
    if(fscanf(f, "%d",&data)==1){
        bst = create_node(data);
    }
    else{
        printf("errore nel formato del file");
        return NULL;
    }
    while(fscanf(f, "%d",&data)==1){
        treeNode** BST=NULL;
        BST=&bst;
        insert_node(BST, data);
    }
    return bst;
}

/**
 * @brief stampa gli antenati di un nodo
 * 
 * @param bst 
 * @param value 
 * @return true 
 * @return false 
 */
bool stampa_antenati(treeNode* bst, int value){
    if(bst==NULL){return false;}
    if(bst->data==value){return true;}
    if(stampa_antenati(bst->left,value) || stampa_antenati(bst->right,value)){
        printf("valore : %d", bst->data);
        return true;
    }
    return false;
}

/**
 * @brief aggiunge un nodo come figio destro di una foglia se il contenuto di essa è uguale alla somma dei nodi tramite i quali ci siamo arrivati
 * 
 * @param bst 
 * @param sum 
 */
void addLeafs(treeNode* bst,int sum){
    if(bst->left==NULL && bst->right==NULL){
        if(sum == bst->data){
            bst->right=create_node(sum+1);
        }
    }
    else{
        if(bst->left!=NULL){
            addLeafs(bst->left, sum+bst->data);
        }
        if(bst->right!=NULL){
            addLeafs(bst->right, sum+bst->data);
        }
    }
}

int main(){
    FILE* f = fopen("BST.txt", "r");  
    treeNode* bst=NULL;        
    if (f != NULL) {
        bst=readFromFile(f);
    }
    else{
        printf("impossibile leggere il file");
        return 0;
    }
    print_pre_order(bst);
    print_post_order(bst);
    return 0;
}