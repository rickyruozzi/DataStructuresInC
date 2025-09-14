#ifndef GRAFOLISTA
#define GRAFOLISTA
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
typedef struct node{
    int vertex;
    int weight;
    struct node* next;
}node;
typedef struct graph{
    int vertex_number;
    node** list; 
}graph;

graph* createGraph(int V);
/*Il secondo parametro consiste in un puntatore che punta ad un 
puntatore di un nodo*/
#endif