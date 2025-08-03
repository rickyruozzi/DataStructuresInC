#include "Graph.h"

/**
 * @brief inizializza il nostro grafo
 * 
 * @param G 
 * @param numVertici 
 */
void initGraph(Graph *G, int numVertici){
    G->vertici = numVertici;
    for(int i=0;i<numVertici;i++){
        for(int j=0;j<numVertici;j++){
            G->matrix[i][j]=0;
        }
    }
}

/**
 * @brief aggiunge un arco
 * 
 * @param G 
 * @param v1 
 * @param v2 
 * @param peso 
 * @param isDirected 
 */
void addEdge(Graph* G, int v1, int v2, int peso, bool isDirected){
    G->matrix[v1][v2] = peso;
    if(!isDirected){
        G->matrix[v2][v1]=peso;
    }
}

/**
 * @brief stampa la matrice delle adiacenze
 * 
 * @param G 
 * @param numVertici 
 */
void printMatrix(Graph* G, int numVertici){
    for(int i=0;i<numVertici;i++){
        for(int j=0;j<numVertici;j++){
            printf("%d -> %d (peso: %d) ",i,j,G->matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief trova il grado di un nodo
 * 
 * @param G 
 * @param numVertici 
 * @param nodo 
 * @return int 
 */
int trovaGrado(Graph* G, int numVertici, int nodo){
    int grado=0;
    for(int i=0;i<numVertici;i++){
        if( G->matrix[nodo][i]){
            grado=grado+1;
        }
    }
    return grado;
}

/**
 * @brief stampa i gradi dei nodi
 * 
 * @param G 
 * @param numVertici 
 */
void stampaGradi(Graph* G, int numVertici){
    for(int i=0;i<numVertici;i++){
        int grado=trovaGrado(G,numVertici,i);
        printf("Nodo %d: grado %d\n",i,grado);
    }
}

/**
 * @brief legge i dati di un grafo dal file e aggiorna i grafo
 * 
 * @param G 
 * @param Filename 
 * @param isDirected 
 */
void ReadGraph(Graph* G, const char *Filename, bool isDirected){
    FILE* f=fopen(Filename,"r");
        if (!f){
        perror("Errore nell'apertura del file");
        return;
    }
    int numVertici;
    int numArchi;
    if(fscanf(f,"%d %d",&numVertici,&numArchi)!=2){
        fprintf(stderr, "errore di formattazione del file di testo");
        fclose(f);
        return;
    }
    initGraph(G, numVertici);
    for(int i=0; i<numArchi;i++){
        int v1, v2, peso;
        if(fscanf(f,"%d %d %d",&v1,&v2,&peso)!=3){
            fprintf(stderr, "errore di formattazione del file di testo");
            fclose(f);
            return;
        }
        addEdge(G,v1,v2,peso,isDirected);
    }
}

/**
 * @brief trova il nodo con distanza minima in dist non visitato
 * 
 * @param dist 
 * @param visitati 
 * @param v 
 * @return int 
 */
int FindMin(int dist[], bool visitati[], int v){
    int min = INT_MAX;
    int min_index = -1;

    for(int i=0; i<v; i++){
        if(!visitati[i] && dist[i] < min){
            min = dist[i];
            min_index=i;
        }
    }
    return min_index;
}

/**
 * @brief calcola i percorsi minimi tra il nodo sorgente e tutti gli altri nodi
 * 
 * @param G 
 * @param dist 
 * @param prev 
 * @param src 
 */
void Djikstra(Graph* G, int dist[], int prev[], int src){
    int vertici= G->vertici;    //numero di vertici
    bool* visitati = (bool*)malloc(vertici*sizeof(bool));
    for(int i=0; i<vertici;i++){    //inizializza i tre array
        visitati[i]=false;
        dist[i]=INT_MAX;
        prev[i]=-1;
    }
    dist[src]=0;    //inizializza la distanza tra il nodo sorgente e se stesso
    for(int i=0;i<G->vertici-1;i++){  //calcoliamo le distanze analizzando 
        int u = FindMin(dist,visitati,G->vertici);  //funzione per trovare il nodo con distanza minima non visitato
        if(u==-1) return;
        visitati[u]=true;   //settiamo su visitato il nodo valutando su visitato
        for(int j=0;j<G->vertici;j++){  //valutiamo tutti i suoi vicini 
            if(G->matrix[u][j] > 0 && !visitati[j] && dist[u] != INT_MAX && dist[u] + G->matrix[u][j] < dist[j]){ //se la distanza tra u e j sommata con la distanza calcolata fino a quel momento tra il nodo sorgente e u è minore dell'attuale distanza tra il nodo sorgente e j allora aggiorniamo i due array
                dist[j]=G->matrix[u][j]+dist[u];
                prev[j]=u;
            }
        }
    }
    for(int i=0;i<G->vertici;i++){
        printf("%d -> %d ", i, dist[i]);    //stampiamo le distanze (facoltatiovo, abbiamo già modificato i due array)
    }
    free(visitati);
}

int main(){
    Graph* G=(Graph*)malloc(sizeof(Graph));
    ReadGraph(G,"G.txt",true);
    printMatrix(G,G->vertici);
    stampaGradi(G,G->vertici);
}