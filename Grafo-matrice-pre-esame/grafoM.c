#include "grafoM.h"

/**
 * @brief inizializza il grafo
 * 
 * @param G 
 * @param numNodes 
 */
void init(grafom* G, int numNodes){
    G->numNodes=numNodes;
    G->matrix=(int**)malloc(sizeof(int*)*numNodes);
    for(int i=0; i<numNodes; i++){
        G->matrix[i]=(int*)malloc(sizeof(int)*numNodes);
        for(int j=0; j<numNodes; j++){
            G->matrix[i][j]=0;
        }
    }
}

/**
 * @brief controlla se il grafo è vuoto
 * 
 * @param G 
 * @return true 
 * @return false 
 */
bool isEmpty(grafom* G){
    return G->numNodes==0;
}

/**
 * @brief aggiunge un arco al grafo
 * 
 * @param G 
 * @param src 
 * @param dest 
 * @param weight 
 */
void addEdge(grafom* G, int src, int dest, int weight){
    if(src>=0 && src<G->numNodes &&dest>=0 && dest<G->numNodes){
        G->matrix[src][dest]=weight;
        G->matrix[dest][src]=weight; 
    }
}

/**
 * @brief rimuove un arco dal grafo
 * 
 * @param G 
 * @param src 
 * @param dest 
 */
void removeEdge(grafom* G, int src, int dest){
    if(src>=0 && src<G->numNodes &&dest>=0 && dest<G->numNodes){
        G->matrix[src][dest]=0;
        G->matrix[dest][src]=0; 
    }
}

/**
 * @brief verifica l'esistenza di un arco
 * 
 * @param G 
 * @param src 
 * @param dest 
 * @return true 
 * @return false 
 */
bool hasEdge(grafom* G, int src, int dest){
    if(src>=0 && src<G->numNodes &&dest>=0 && dest<G->numNodes){
        return G->matrix[src][dest]!=0;
    }
    return false;
}

/**
 * @brief stampa il grafo
 * 
 * @param G 
 */
void printGraph(grafom* G){
    for(int i=0; i<G->numNodes; i++){
        for(int j=0; j<G->numNodes;j++){
            printf("%d", G->matrix[i][j]);
        }
    }
}

void freeGraph(grafom* G){
    for(int i=0; i<G->numNodes; i++){
        free(G->matrix[i]);
    }
    free(G->matrix);
    free(G);
}

/**
 * @brief trova il nodo meno distante non visitato
 * 
 * @param visited 
 * @param dist 
 * @param v 
 * @return int 
 */
int trova_minimo(bool* visited, int* dist, int v){
    int min=INT_MAX;
    int index=-1;
    for(int i=0; i<v; i++){
        if(!visited[i] && min>dist[i]){
            min=dist[i];
            index=i;
        }
    }
    return index;
}

/**
 * @brief trova i cammini minimi da src ad ogni altro nodo
 * 
 * @param G 
 * @param src 
 * @return int* 
 */
void Dijkstra(grafom* G, int src, int* dist, int* prev){
    bool* visited=(bool*)malloc(sizeof(bool)*G->numNodes);
    for(int i=0; i<G->numNodes; i++){
        dist[i]=INT_MAX;
        prev[i]=-1;
        visited[i]=false;
    }
    dist[src]=0;
    for(int j=0;j<G->numNodes;j++){
        int u=trova_minimo(visited, dist, G->numNodes);
        if(u==-1){
            free(visited);
            return;
        }
        visited[u]=true;
        for(int j=0; j<G->numNodes; j++){
            if(G->matrix[u][j]!=0 && dist[u]!=INT_MAX && !visited[j] && dist[j]>dist[u]+G->matrix[u][j]){
                dist[j]=dist[u]+G->matrix[u][j];
                prev[j]=u;
            }
        }
    }
    free(visited);
}

void bellmanFord(grafom* G, int src, int* prev, int* dist) {
    for (int i = 0; i < G->numNodes; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[src] = 0;

    // Relax edges (V-1) times
    for (int i = 0; i < G->numNodes - 1; i++) {
        for (int j = 0; j < G->numNodes; j++) {
            for (int k = 0; k < G->numNodes; k++) {
                if (G->matrix[j][k] != 0 && dist[j] != INT_MAX && dist[k] > dist[j] + G->matrix[j][k]) {
                    dist[k] = dist[j] + G->matrix[j][k];
                    prev[k] = j;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < G->numNodes; i++) {
        for (int j = 0; j < G->numNodes; j++) {
            if (G->matrix[i][j] != 0 && dist[i] != INT_MAX && dist[j] > dist[i] + G->matrix[i][j]) {
                printf("individuato ciclo negativo!!");
                return;
            }
        }
    }
}
int main() {
    int n = 4;
    grafom* G = (grafom*)malloc(sizeof(grafom));
    init(G, n);

    // Aggiungi archi
    addEdge(G, 0, 1, 7);
    addEdge(G, 0, 2, 3);
    addEdge(G, 1, 2, 1);
    addEdge(G, 1, 3, 4);
    addEdge(G, 2, 3, 2);

    printf("Matrice di adiacenza:\n");
    printGraph(G);
    printf("\n");

    // Test Dijkstra
    int dist[n], prev[n];
    Dijkstra(G, 0, dist, prev);
    printf("Distanze minime da 0 (Dijkstra):\n");
    for(int i = 0; i < n; i++) {
        printf("Nodo %d: distanza = %d, predecessore = %d\n", i, dist[i], prev[i]);
    }

    // Test Bellman-Ford
    bellmanFord(G, 0, prev, dist);
    printf("Distanze minime da 0 (Bellman-Ford):\n");
    for(int i = 0; i < n; i++) {
        printf("Nodo %d: distanza = %d, predecessore = %d\n", i, dist[i], prev[i]);
    }

    // Test hasEdge e removeEdge
    printf("Esiste arco 0-1? %s\n", hasEdge(G, 0, 1) ? "Sì" : "No");
    removeEdge(G, 0, 1);
    printf("Dopo rimozione, esiste arco 0-1? %s\n", hasEdge(G, 0, 1) ? "Sì" : "No");

    freeGraph(G);
    return 0;
}