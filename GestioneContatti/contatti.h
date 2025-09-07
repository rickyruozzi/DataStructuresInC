#ifndef CONTATTI_H
#define CONTATTI_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LEN 100
typedef struct contatto{
    char nome[MAX_LEN];
    char cognome[MAX_LEN];
    int numero;
    struct contatto* next;
} contatto;
contatto* crearubrica();
void aggiungiContatto(contatto* rubrica);
void eliminaContatto(contatto* rubrica);
void stampaContatti(contatto* rubrica);
#endif