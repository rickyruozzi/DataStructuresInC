#ifndef GRAFO_MATRICE
#define GRAFO_MATRICE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NODI 100
typedef struct Graph{
    int vertici;
    int matrix[MAX_NODI][MAX_NODI];
}Graph;
void initGraph(Graph *G, int numVertici);
void addEdge(Graph* G, int v1, int v2, int peso, bool isDirected);
void printMatrix(Graph* G, int numVertici);
int trovaGrado(Graph* G, int numVertici, int nodo);
void stampaGradi(Graph* G, int numVertici);
void ReadGraph(Graph* G, const char *Filename, bool isDirected);
#endif