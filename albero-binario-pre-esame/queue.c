#include "queue.h"
/**
 * @brief Create a Queue object
 * 
 * @param capacity 
 * @return Queue* 
 */
Queue* createQueue(int capacity){
    Queue* Q=(Queue*)malloc(sizeof(Queue));
    Q->data=(Node*)malloc(capacity*sizeof(Node));
    Q->front=0;
    Q->rear=-1;
    Q->size=0;
    Q->capacity=capacity;
    return Q;
}

void freeQueue(Queue* q){if (q) free(q);}

bool isEmpty(Queue* q){
    if (q->size==0) return true;
    return false;
}

bool isFull(Queue* q){
    if(q->size==q->capacity) return true;
    return false;
}

void enqueue(Queue *q, Node* nodo){
    if(isFull(q)){
        printf("Coda già piena\n");
        return;
    }
    q->rear=(q->rear+1)%q->capacity;
    q->data[q->rear]=nodo;
    q->size++;
}

Node* dequeue(Queue * q){
    if(isEmpty(q)){
        printf("Coda vuota\n");
        return NULL;
    }
    Node* nodo = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return nodo;
}

Node* peek(Queue* q){
    if(isEmpty(q)){
        printf("Coda vuota\n");
        return NULL;
    }
    return q->data[q->front];
}

int main(){}