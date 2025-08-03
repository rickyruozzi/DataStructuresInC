#include "Graph.h"

void initGraph(Graph *G, int numVertici){
    G->vertici = numVertici;
    for(int i=0;i<numVertici;i++){
        for(int j=0;j<numVertici;j++){
            G->matrix[i][j]=0;
        }
    }
}

void addEdge(Graph* G, int v1, int v2, int peso, bool isDirected){
    G->matrix[v1][v2] = peso;
    if(!isDirected){
        G->matrix[v2][v1]=peso;
    }
}

void ReadGraph(Graph* G, const char *Filename, bool isDirected){
    FILE* f=fopen(Filename,"r");
        if (!f){
        perror("Errore nell'apertura del file");
        return NULL;
    }
    int numVertici;
    int numArchi;
    if(fscanf(f,"%d %d",&numVertici,&numArchi)!=2){
        fprintf(stderr, "errore di formattazione del file di testo");
        fclose(f);
        return NULL;
    }
    initGraph(G, numVertici);
    for(int i=0; i<numArchi;i++){
        int v1, v2, peso;
        if(fscanf(f,"%d %d %d",&v1,&v2,&peso)!=2){
            fprintf(stderr, "errore di formattazione del file di testo");
            fclose(f);
            return NULL;
        }
        addEdge(G,v1,v2,peso,isDirected);
    }
}
int main(){}