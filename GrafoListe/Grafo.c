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

/**
 * @brief trova il nodo con distanza minima non visitato (così garantamo la logica greedy)
 * 
 * @note sostituibile con un algoritmo che si basi sulla coda con priorità
 * 
 * @param visitato 
 * @param dist 
 * @param V 
 * @return int 
 */
int trova_minimo(bool visitato[], int dist[], int V ){
    int min = INT_MAX;
    int min_index = -1;

    for(int i=0; i<V; i++){
        if(!visitato[i] && dist[i] < min){
            min = dist[i];
            min_index=i;
        }
    }
    return min_index;
}

/**
 * @brief calcola le distanza minime
 * 
 * @param src 
 * @param dist 
 * @param prev 
 * @param Grafo 
 * @return int* 
 * 
 * @note l'array delle visite serve per evitare eventuali cicli
 * @note trova_minimo serve per trovare il vertice più vicino a quelli già visitati (permette di attuare la logica greedy)
 */
void Dijkstra(int src, int* dist, int* prev, grafo* Grafo){
    //inizializzazione
    int vertici= Grafo->vertici;
    bool* visitati = (bool*)malloc(vertici*sizeof(bool));
    for(int i=0; i<vertici;i++){
        visitati[i]=false;
        dist[i]=INT_MAX;
        prev[i]=-1;
    }
    dist[src]=0;

    //calcolo delle distanza minime e dei cammini
    for(int j=0; j<vertici-1; j++){
        int u=trova_minimo(visitati, dist, vertici);
        if (u==-1){return;} //se non troviamo nodi non visitati raggiungibili allora non possiamo continuare con l'algoritmo
        visitati[u]=true;
        Nodo* current=Grafo->adjacency_list[u]; //testa della lista di adiacenza del nodo u
        while (current!=NULL){
            int v=current->vertex;
            int peso = current->peso;
            if(!visitati[v] && dist[u]!=INT_MAX && dist[v]>dist[u]+peso){
                dist[v]=dist[u]+peso;
                prev[v]=u;
            }
            current=current->next;
        }
    }
    free(visitati);
}
int time = 0; 
/**
 * @brief permette di cercare un ciclo nel grafo
 * 
 * @param grafo 
 * @return true 
 * @return false 
 */
bool cerca_ciclo(grafo* grafo){
    int pre[grafo->vertici];
    int post[grafo->vertici];
    time=0;
    for(int i=0; i<grafo->vertici;i++){
        pre[i]=0;
        post[i]=0;
    }
    for(int i=0; i<grafo->vertici; i++){
        if(pre[i]==0 && ciclo(grafo, pre, post, i, -1)){ // passa -1 come padre iniziale
            return true;
        }
    }
    return false;
}

bool ciclo(grafo* Grafo, int pre[], int post[], int v, int padre){
    time=time+1;
    pre[v]=time;
    Nodo* testa=Grafo->adjacency_list[v];
    while(testa!=NULL){
        if(pre[testa->vertex]==0){
            if(ciclo(Grafo, pre, post, testa->vertex, v)){return true;}
        }
        else{
            if(post[testa->vertex]==0 && testa->vertex != padre){
                return true;
            }
        }
        testa=testa->next;
    }
    time=time+1;
    post[v]=time;
    return false;
}

/**
 * @brief Bellman Ford per i cammini minimi da src agli altri nodi raggiungibili del grafo
 * 
 * @param G 
 * @param dist 
 * @param prev 
 * @param src 
 */
void BellmanFord(grafo* G, int* dist, int* prev, int src){
    int v= G->vertici;
    for(int i=0; i<v; i++){
        dist[i]=INT_MAX;
        prev[i]=-1;
    }
    dist[src]=0;
    for(int i=0; i<v; i++){
        for(int j=0; j<v; j++){
            Nodo* current = G->adjacency_list[j];
            while(current!=NULL){
                int v=current->vertex;
                int w=current->peso;
                if(dist[j]!=INT_MAX && dist[v]>dist[j]+w){
                    dist[v]=dist[j]+w;
                    prev[v]=j;
                }
                current=current->next;
            }
        }
    }
    for(int i=0; i<v; i++){
        Nodo* current=G->adjacency_list[i];
        while(current!=NULL){
            int w=current->peso;
            int v=current->vertex;
            if(dist[i]+w<dist[v]){
                printf("Ciclo negativo individuato!");
                free(dist);
                return;
            }
            current=current->next;
        }
    }
}

int main(){
    grafo* Grafo = loadGraphFromFile("Grafo.txt", true);
    printGraph(Grafo);
    if(isUndirected(Grafo)){
        printf("Grafo non diretto");
    }
    else{
        printf("Grafo diretto");
    }
    int* dist = (int*)malloc(Grafo->vertici*sizeof(int));
    int* prev = (int*)malloc(Grafo->vertici*sizeof(int));
    Dijkstra(0, dist, prev, Grafo);
    printf("\nDistanze minime dal nodo 0:\n");
    for(int i=0; i<Grafo->vertici; i++){
        printf("Nodo %d: Distanza = %d, Precedente = %d\n", i, dist[i], prev[i]);
    }
    BellmanFord(Grafo, dist, prev, 0);
    if(cerca_ciclo(Grafo)){
        printf("Ciclo trovato\n");
    }
    else{
        printf("Nessun ciclo trovato\n");
    }
    int* dist2 = (int*)malloc(Grafo->vertici*sizeof(int));
    int* prev2 = (int*)malloc(Grafo->vertici*sizeof(int));
    BellmanFord(Grafo, dist2, prev2, 0);
    for(int i=0; i<Grafo->vertici; i++){
        printf("Nodo %d: Distanza = %d, Precedente = %d\n", i, dist[i], prev[i]);
    }
    free(dist);
    free(prev);
    free(dist2);
    free(prev2);
    freeGraph(Grafo);
    return 0;
}