#include "GrafoLista.h"
#include <limits.h>
/**
 * @brief Create a Graph
 * 
 * @param V 
 */
graph* createGraph(int V){
    graph* G=(graph*)malloc(sizeof(graph));
    if(!G) return NULL;
    G->vertex_number=V;
    G->list=(node**)malloc(sizeof(node*)*V);
    for(int i=0; i<V;i++){
        G->list[i]=NULL;
    }
    return G;
}

/**
 * @brief Create a Node object
 * 
 * @param dest 
 * @param weight 
 * @return node* 
 */
node* createNode(int dest, int weight){
    node* NewNode=(node*)malloc(sizeof(node));
    NewNode->next=NULL;
    NewNode->vertex=dest;
    NewNode->weight=weight;
    return NewNode;
}

/**
 * @brief Add an edge to the graph
 * 
 * @param G 
 * @param src 
 * @param dest 
 * @param weight 
 */
void addEdge(graph* G, int src, int dest, int weight){
    if (src < 0 || src >= G->vertex_number){
        fprintf(stderr, "Errore: indice src fuori range\n");
        return;
    }
    node* N=createNode(dest,weight);
    node* testa=G->list[src];
    if(testa==NULL){
        G->list[src]=N;
        return;
    }
    while(testa->next!=NULL){
        testa=testa->next;
    }
    testa->next=N;
}

graph* readGraphFromFile(const char* filename, bool isDirected){
    FILE* f=fopen(filename, "r");
    if (!f){
        perror("Errore nell'apertura del file");
        return NULL;
    }
    int vertici;
    int archi;
    if(fscanf(f, "%d %d", &vertici, &archi)!=2){
        printf("Errore nella formattazione del file di testo");
        return NULL;
    }
    graph* G=createGraph(vertici);
    for(int i=0; i<archi;i++){
        int src;
        int dest;
        int weight;
        fscanf(f, "%d %d %d", &src, &dest, &weight);
        addEdge(G, src, dest, weight);
        if(!isDirected){
            addEdge(G, dest, src, weight);
        }
    }
}

void removeEdge(graph* G, int src, int dest,bool  isDirected){
    if(G->list[src]==NULL) return;
    node* testa=G->list[src];
    if(testa->vertex==dest){
        G->list[src]=testa->next;
        free(testa);
        return;
    }
    while(testa->next!=NULL && testa->next->vertex!=dest){
        testa=testa->next;
    }
    if(testa->next!=NULL){
        node* temp=testa->next;
        testa->next=temp->next;
        free(temp);
    }
    if(!isDirected){
        node* testa2=G->list[dest];
        if(testa2->vertex==src){
            G->list[dest]=testa2->next;
            free(testa2);
            return;
        }
        while(testa2->next!=NULL && testa2->next->vertex!=src){
            testa2=testa2->next;
        }
        if(testa2->next!=NULL){
            node* temp=testa2->next;
            testa2->next=temp->next;
            free(temp);
        }
    }
}

/**
 * @brief trova il nodo meno distante non visitato
 * 
 * @param visited 
 * @param dist 
 * @param v 
 * @return int 
 */
int trova_minimo(bool* visited, int* dist, int v){
    int min=INT_MAX;
    int index=-1;
    for(int i=0; i<v; i++){
        if(!visited[i] && min>dist[i]){
            min=dist[i];
            index=i;
        }
    }
    return index;
}

/**
 * @brief trova i cammini minimi da src ad ogni altro nodo
 * 
 * @param G 
 * @param src 
 * @return int* 
 */
void* Djikstra(graph* G, int src, int* dist, int* prev){
    bool* visited=(bool*)malloc(sizeof(bool)*G->vertex_number);
    for(int i=0; i<G->vertex_number; i++){
        dist[i]=INT_MAX;
        prev[i]=-1;
        visited[i]=false;
    }
    dist[src]=0;
    for(int j=0;j<G->vertex_number;j++){
        int u=trova_minimo(visited, dist, G->vertex_number);
        if(u==-1) return;
        visited[u]=true;
        node* current= G->list[src];
        while(current!=NULL){
            int v= current->vertex;
            int w=current->weight;
            if(!visited[v] && dist[u]!=INT_MAX && dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                prev[v]=u;
            }
            current=current->next;
        }
    }
}
/*
1-inizializzazione
2-scorrimento
3-individuazione del nodo non visitato meno distante
4-controllo delle distanze (il nodo non deve essere visitato, deve essere raggiungibile 
dalla sorgente e la distanza calcolata deve essere inferiore a quelle calcolate in precedenza)
*/


int time=0;
/**
 * @brief controlla la presenza di cicli nel grafo
 * 
 * @param G 
 * @param pre 
 * @param post 
 * @param v 
 * @return true 
 * @return false 
 */
bool searchCycle(graph* G, int* pre, int* post, int v){
    time=time+1;
    pre[v]=time;
    node* current=G->list[v];
    while(current!=NULL){
        if(pre[current->vertex]==0){
            if (searchCycle(G,pre,post,current->vertex)) return true;
        }
        else{
            if(post[current->vertex]==0) return true;
        }
        current=current->next;
    }
    time=time+1;
    post[v]=time;
    return false;
}
int main(){}