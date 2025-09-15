#ifndef GRAFO_MATRICE_PRE_ESAME
#define GRAFO_MATRICE_PRE_ESAME
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct grafom{
    int** matrix;   //array di array (matrice)
    int numNodes;
}grafom;
void init(grafom* g, int numNodes);
bool isEmpty(grafom* g);
void addEdge(grafom* g, int src, int dest, int weight);
void removeEdge(grafom* g, int src, int dest);
bool hasEdge(grafom* g, int src, int dest);
void printGraph(grafom* g);
void freeGraph(grafom* g);
#endif