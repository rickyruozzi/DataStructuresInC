#include "./Grafo.h"

grafo* createGraph(int vertici){
    grafo* g = (grafo*)malloc(sizeof(grafo));
    g->vertici = vertici;   
    g->adjacency_list = (Nodo**)malloc(sizeof(Nodo*)*vertici);
    for(int i=0; i<vertici; i++){
        g->adjacency_list[i] = NULL;
    }
    return g;
}

Nodo* createNode(int dest, int peso){
    Nodo* newNodo = (Nodo*)malloc(sizeof(Nodo));
    newNodo->vertex=dest;
    newNodo->peso=peso;
    newNodo->next=NULL;
    return newNodo;
}

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

void printGraph(grafo* g){
    for(int i=0; i<g->vertici; i++){
        Nodo* testa=g->adjacency_list[i];        while(testa!=NULL){
            printf("%d -> %d (peso: %d)\n", i, testa->vertex, testa->peso);
            testa=testa->next;
        }
    }
}

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

bool isDirected(grafo* g){
    if(!isUndirected(g)) return true;
    return false;
}

int main(){
    grafo* Grafo = loadGraphFromFile("Grafo.txt", false);
    printGraph(Grafo);
    freeGraph(Grafo);
}