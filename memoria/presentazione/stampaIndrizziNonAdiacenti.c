#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodo{
    int valore;
    struct nodo* next;
}nodo;

nodo* aggiungiNodo(nodo* testa){
    nodo* nuovoNodo = (nodo*)malloc(sizeof(nodo));
    nuovoNodo->valore = rand()%100;
    nuovoNodo->next = testa;
    return nuovoNodo;
}

void stampa(nodo* testa){
    nodo* n = testa;
    printf(" indirizzo nodo  | valore | indirizzo puntato\n");
    printf("---------------------------------------------\n");
    while(n != NULL){
        printf("   %p    |   %d   |     %p\n", n, n->valore, n->next);
        n = n->next;
    }
}

void dealloca(nodo* testa){
    nodo* n = testa;
    printf("---------------------------------------------\n");
    while(testa != NULL){
        n = testa;
        testa = testa->next;
        free(n);
    }
}

int main(){

    printf("Programma che stampa gli indirizzi non adiacenti di memoria.\n\n");

    nodo* testa = (nodo*)malloc(sizeof(nodo));
    testa = NULL;

    for(int i=0; i<10; i++)
        testa = aggiungiNodo(testa);
    stampa(testa);
    dealloca(testa);

    return 0;
    
}


