#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>

typedef struct Nodo{
    int info;
    struct Nodo* next;
}Nodo;

typedef struct Coda{
    Nodo* head;
    Nodo* tail;
    int numElementi;
}Coda;

//inserimento in coda
void enqueue(Coda* coda, int num){
    Nodo* nodo = (Nodo*) mmap(NULL, sizeof(Nodo), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);

    nodo->info = num;
    nodo->next = NULL;

    if (coda->head == NULL)
        coda->head = nodo;
    // else{
    //     Nodo* index = coda->head;
    //     while(index->next != NULL){
    //         index = index->next;
    //     }
    //     index->next = nodo;
    // }
    else
        coda->tail->next = nodo;
    
    coda->tail = nodo;
    coda->numElementi++;
}


//rimozione del nodo in testa
int dequeue(Coda* coda){
    Nodo* tmp = coda->head;
    int valore = tmp->info;
    munmap(tmp, sizeof(Nodo));
    coda->head = coda->head->next;
    coda->numElementi--;
    return valore;
}

void stampa(Coda* coda){
    Nodo* nodo = coda->head;

    if (coda->head == NULL)
        printf("Coda vuota\n");
    else{
        while (nodo != NULL) {
            printf("[%d]\n", nodo->info);
            nodo = nodo->next;
        }
        printf("Qui");
    }
}