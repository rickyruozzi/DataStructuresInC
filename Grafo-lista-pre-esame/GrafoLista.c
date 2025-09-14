#include "GrafoLista.h"
/**
 * @brief Create a Graph
 * 
 * @param V 
 */
graph* createGraph(int V){
    graph* G=(graph*)malloc(sizeof(graph));
    if(!G) return NULL;
    G->vertex_number=V;
    G->list=(node**)malloc(sizeof(node*)*V);
    for(int i=0; i<V;i++){
        G->list[i]=NULL;
    }
    return G;
}

/**
 * @brief Create a Node object
 * 
 * @param dest 
 * @param weight 
 * @return node* 
 */
node* createNode(int dest, int weight){
    node* NewNode=(node*)malloc(sizeof(node));
    NewNode->next=NULL;
    NewNode->vertex=dest;
    NewNode->weight=weight;
    return NewNode;
}

/**
 * @brief Add an edge to the graph
 * 
 * @param G 
 * @param src 
 * @param dest 
 * @param weight 
 */
void addEdge(graph* G, int src, int dest, int weight){
    if (src < 0 || src >= G->vertex_number){
        fprintf(stderr, "Errore: indice src fuori range\n");
        return;
    }
    node* N=createNode(dest,weight);
    node* testa=G->list[src];
    if(testa==NULL){
        G->list[src]=N;
        return;
    }
    while(testa->next!=NULL){
        testa=testa->next;
    }
    testa->next=N;
}

graph* readGraphFromFile(const char* filename, bool isDirected){
    FILE* f=fopen(filename, "r");
    if (!f){
        perror("Errore nell'apertura del file");
        return NULL;
    }
    int vertici;
    int archi;
    if(fscanf(f, "%d %d", &vertici, &archi)!=2){
        printf("Errore nella formattazione del file di testo");
        return NULL;
    }
    graph* G=createGraph(vertici);
    for(int i=0; i<archi;i++){
        int src;
        int dest;
        int weight;
        fscanf(f, "%d %d %d", &src, &dest, &weight);
        addEdge(G, src, dest, weight);
        if(!isDirected){
            addEdge(G, dest, src, weight);
        }
    }
}
int main(){}