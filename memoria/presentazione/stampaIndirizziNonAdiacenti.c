#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodo{
    int valore;
    struct nodo* next;
}nodo;

nodo* aggiungiNodo(nodo* testa){
    nodo* nuovoNodo = (nodo*)malloc(sizeof(nodo));
    nuovoNodo->valore = rand()%80+10;
    nuovoNodo->next = testa;
    return nuovoNodo;
}

void stampa(nodo* testa){
    int i = 1;
    nodo* n = testa;
    printf(" n-nodo | indirizzo nodo  | valore | indirizzo puntato\n");
    printf("------------------------------------------------------\n");
    while(n != NULL){
        printf("%i       |   %p    |   %d   |     %p\n",i,  n, n->valore, n->next);
        n = n->next;
        i++;
    }
}

void dealloca(nodo* testa){
    nodo* n = testa;
    while(testa != NULL){
        n = testa;
        testa = testa->next;
        free(n);
    }
}

int main(){

    printf("Programma che stampa gli indirizzi di memoria di una struttura dati lista\n");
    printf("di lunghezza variabile.\n");
    printf("[Nota] Sono indirizzi di memoria non adiacenti ma casuali.\n\n");


    srand(time(NULL));

    nodo* testa = (nodo*)malloc(sizeof(nodo));
    testa = NULL;

    for(int i=0; i<(rand()%9)+1; i++)
        testa = aggiungiNodo(testa);
    stampa(testa);
    dealloca(testa);

    return 0;
    
}


