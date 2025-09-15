#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>   // per usare printf e scanf
#include <stdlib.h>  // per usare malloc e free
#include <stdbool.h>  // per usare il tipo bool


typedef struct Node{
    int value;
    struct Node* left;
    struct Node* right;
}Node;
// Struttura della coda
typedef struct {
    Node* data;  // array per memorizzare gli elementi della coda
    int front;      // indice del primo elemento
    int rear;       // indice dell'ultimo elemento
    int size;       // numero di elementi presenti
    int capacity;   // capacità massima della coda
} Queue;

// Funzioni disponibili
Queue* createQueue(int capacity);
void freeQueue(Queue* q);

bool isEmpty(Queue* q);
bool isFull(Queue* q);

void enqueue(Queue* q, int value);
int dequeue(Queue* q);

int peek(Queue* q);   // restituisce l'elemento in testa senza rimuoverlo

#endif
