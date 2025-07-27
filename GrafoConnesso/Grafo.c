#include "./Grafo.h"
/**
 * @brief Create a Graph object
 * 
 * @param vertici 
 * @return grafo* 
 */
grafo* createGraph(int vertici){
    grafo* g = (grafo*)malloc(sizeof(grafo));
    g->vertici = vertici;   
    g->adjacency_list = (Nodo**)malloc(sizeof(Nodo*)*vertici);
    for(int i=0; i<vertici; i++){
        g->adjacency_list[i] = NULL;
    }
    return g;
}

/**
 * @brief Create a Node object
 * 
 * @param dest 
 * @param peso 
 * @return Nodo* 
 */
Nodo* createNode(int dest, int peso){
    Nodo* newNodo = (Nodo*)malloc(sizeof(Nodo));
    newNodo->vertex=dest;
    newNodo->peso=peso;
    newNodo->next=NULL;
    return newNodo;
}

/**
 * @brief add an edge
 * 
 * @param g 
 * @param src 
 * @param dest 
 * @param peso 
 */
void addEdge(grafo* g, int src, int dest, int peso){
    if (src < 0 || src >= g->vertici) {
    fprintf(stderr, "Errore: indice src fuori range\n");
    return;
    }
    Nodo* newNodo = createNode(dest, peso);
    Nodo* testa = g->adjacency_list[src];
    if(testa==NULL){
        g->adjacency_list[src]=newNodo;
        return;
    }
    while(testa->next!=NULL){
        testa=testa->next;
    }
    testa->next=newNodo;
}

/**
 * @brief load the graph from a file
 * 
 * @param filename 
 * @param isDirected 
 * @return grafo* 
 */
grafo* loadGraphFromFile(const char* filename, int isDirected){
    FILE* file = fopen(filename, "r");
    if (!file){
        perror("Errore nell'apertura del file");
        return NULL;
    }
    int numVertici;
    int numArchi;
    if (fscanf(file, "%d %d", &numVertici, &numArchi) != 2) {
        fprintf(stderr, "Formato file non valido.\n");
        fclose(file);
        return NULL;
    }
    grafo* g = createGraph(numVertici);
    for(int i=0; i<numArchi; i++){
        int src,dest,peso;
        fscanf(file, "%d %d %d", &src, &dest, &peso);
        addEdge(g, src, dest, peso);
        if(!isDirected){
            addEdge(g, dest,src,peso);
        }
    }
    fclose(file);
    return g;
}

/**
 * @brief print a graph
 * 
 * @param g 
 */
void printGraph(grafo* g){
    for(int i=0; i<g->vertici; i++){
        Nodo* testa=g->adjacency_list[i];        while(testa!=NULL){
            printf("%d -> %d (peso: %d)\n", i, testa->vertex, testa->peso);
            testa=testa->next;
        }
    }
}

/**
 * @brief free the allocated space for the graph
 * 
 * @param g 
 */
void freeGraph(grafo* g){
    for(int i=0; i<g->vertici; i++){
        Nodo* testa = g->adjacency_list[i];
        while(testa!=NULL){
            Nodo* next = testa->next;
            free(testa);
            testa=next;
        }
    }
    free(g->adjacency_list);
    free(g);
}

/**
 * @brief verify an edge existence
 * 
 * @param g 
 * @param src 
 * @param dest 
 * @return true 
 * @return false 
 */
bool edgeExist(grafo* g, int src, int dest){
    Nodo* testa=g->adjacency_list[src];
    while(testa!=NULL){
        if(testa->vertex==dest){
            return true;
        }
        testa=testa->next;
    }
    return false;
}

/**
 * @brief find an edge weight
 * 
 * @param g 
 * @param src 
 * @param dest 
 * @return int 
 */
int weight(grafo* g, int src, int dest){
    Nodo* testa=g->adjacency_list[src];
    while(testa!=NULL){
        if(testa->vertex==dest){
            return testa->peso;
        }
        testa=testa->next;
    }
    return -1;
}

/**
 * @brief check if the graph is undirected
 * 
 * @param g 
 * @return true 
 * @return false 
 */
bool isUndirected(grafo* g){
    for(int i=0; i<g->vertici; i++){
        Nodo* testa=g->adjacency_list[i];        
        while(testa!=NULL){
            if(!edgeExist(g, testa->vertex, i) || testa->peso!=weight(g,testa->vertex,i)){
                return false;
            }
            testa=testa->next;
        }
    }
    return true;
}

/**
 * @brief check if the graph is directed
 * 
 * @param g 
 * @return true 
 * @return false 
 */
bool isDirected(grafo* g){
    if(!isUndirected(g)) return true;
    return false;
}

int main(){
    grafo* Grafo = loadGraphFromFile("Grafo.txt", true);
    printGraph(Grafo);
    freeGraph(Grafo);
    if(isUndirected(Grafo)){
        printf("Grafo non diretto");
    }
    else{
        printf("Grafo diretto");
    }
    return 0;
}