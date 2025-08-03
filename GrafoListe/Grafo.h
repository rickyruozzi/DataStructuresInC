#ifndef GRAFO_H
#define GRAFO_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Nodo {
    int vertex;
    int peso;
    struct Nodo* next;
} Nodo;
typedef struct grafo{
    int vertici;
    Nodo** adjacency_list;
} grafo;

grafo* loadGraphFromFile(const char* filename, int isDirected);
grafo* createGraph(int vertici);
Nodo* createNode(int vertex, int peso);
void addEdge(grafo* g, int src, int dest, int peso);
void printGraph(grafo* g);
void freeGraph(grafo* graph);
bool edgeExist(grafo* g, int src, int dest);
int weight(grafo* g, int src, int dest);
bool isUndirected(grafo* g);
bool isDirected(grafo* g);
int* Djikstra(int src, int* dist, int* prev, grafo* Grafo);

#endif