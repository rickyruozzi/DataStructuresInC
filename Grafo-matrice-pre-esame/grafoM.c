#include "grafoM.h"

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

bool isEmpty(grafom* G){
    return G->numNodes==0;
}

void addEdge(grafom* G, int src, int dest, int weight){
    if(src>0 && src<G->numNodes &&dest>0 && dest<G->numNodes){
        G->matrix[src][dest]=weight;
        G->matrix[dest][src]=weight; 
    }
}

void removeEdge(grafom* G, int src, int dest){
    if(src>0 && src<G->numNodes &&dest>0 && dest<G->numNodes){
        G->matrix[src][dest]=0;
        G->matrix[dest][src]=0; 
    }
}

int main(){}