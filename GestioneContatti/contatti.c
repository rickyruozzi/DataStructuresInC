#include "contatti.h"
#define MIO_NUMERO 123456789
#define MIO_NOME "Riccardo"
#define MIO_COGNOME "Ruozzi"

/**
 * @brief crea la nostra lista per la rubrica
 * 
 * @return contatto* 
 */
contatto* creaRubrica(){
    contatto* rubrica = (contatto*)malloc(sizeof(contatto));
    rubrica->numero=MIO_NUMERO;
    strncpy(rubrica->nome,MIO_NOME, sizeof(rubrica->nome));
    strncpy(rubrica->cognome,MIO_COGNOME, sizeof(rubrica->cognome));
    rubrica->next=NULL;
    return rubrica;
}
/**
 * @brief aggiunge un contatto alla rubrica
 * 
 * @param rubrica 
 */
void aggiungiContatto(contatto* rubrica){
    contatto* current=rubrica;
    while(current->next!=NULL){
        current=current->next;
    }
    contatto* newContatto= (contatto*)malloc(sizeof(contatto));
    int numero;
    char nome[MAX_LEN];
    char cognome[MAX_LEN];
    printf("inserire il numero di telefono: ");
    scanf("%d", &numero);
    newContatto->numero=numero;
    printf("inserire il nome del contatto: ");
    scanf("%49s", nome);
    printf("inserire il cognome del contatto: ");
    scanf("%49s", cognome);
    strncpy(newContatto->nome,nome, sizeof(newContatto->nome));
    strncpy(newContatto->cognome,cognome, sizeof(newContatto->cognome));
    newContatto->nome[MAX_LEN - 1] = '\0';
    newContatto->cognome[MAX_LEN - 1] = '\0';
    newContatto->next=NULL;
    current->next=newContatto;
}

/**
 * @brief elimina un nodo dalla rubrica
 * 
 * @param rubrica 
 */
void eliminaContatto(contatto* rubrica){
    int numero;
    printf("inserire il numero del contatto da eliminare: ");
    scanf("%d", &numero);
    contatto* current=rubrica;
    while(current->next!=NULL && numero!=current->next->numero){
        current=current->next;
    }
    if(current->next==NULL){
        return;
    }
    if(current->next->numero==numero){
        contatto* temp=current->next;
        current->next=temp->next;
        free(temp);
    }
}

/**
 * @brief stampa i contatti
 * 
 * @param rubrica 
 */
void stampaContatti(contatto* rubrica){
    contatto* current=rubrica;
    while(current!=NULL){
        printf("Nome: %s \n", current->nome);
        printf("Cognome: %s \n", current->cognome);
        printf("Numero di telefono: %d \n", current->numero);
        current=current->next;
    }
}

int main(){
    contatto *rubrica=creaRubrica();
    aggiungiContatto(rubrica);
}