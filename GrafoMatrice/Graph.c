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
int main(){
    Graph* G=(Graph*)malloc(sizeof(Graph));
    ReadGraph(G,"G.txt",true);
    printMatrix(G,G->vertici);
    stampaGradi(G,G->vertici);
}