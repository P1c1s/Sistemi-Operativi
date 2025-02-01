#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/mman.h>

#define DIM 10

typedef struct Nodo{
    int info;
    struct Nodo* next; 
} Nodo;

Nodo* head = NULL;
Nodo* last = NULL;

Nodo* allocazione();
Nodo* inserimento(int);
Nodo* rimozione();
void stampa();

int main(){
    srand(time(NULL));
    printf("Inserisci un numero random di numeri all'interno di una pila\n\n");

    int ins = rand()%10;

    printf("Inserisci %d valori:\n", ins);

    for(int i=0; i<ins; i++){
        int num;
        printf("Inserisci valore:\t");
        scanf("%d", &num);
        inserimento(num);
    }

    stampa();

    int rim = rand()%ins;
    printf("Rimossi %d elementi:\n", rim);

    for(int i=0; i<rim; i++){
        head = rimozione();
    }

    stampa();

    return 0;
}

Nodo* inserimento(int num){
    Nodo* nodo = allocazione();
    nodo->info = num;
    nodo->next = NULL;

    if(head == NULL)
        head = nodo;
    else{
        Nodo* temp = head;
        head = nodo;
        head->next = temp;
    }
    return nodo;
}

Nodo* allocazione(){
    return (Nodo*) mmap(NULL, sizeof(Nodo), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
}

Nodo* rimozione(){
    Nodo* temp = head->next;
    munmap(head, sizeof(Nodo));
    return temp;
}

void stampa(){
    Nodo* nodo = head;
    while(nodo!= NULL){
        printf("[%d]\n", nodo->info);
        nodo = nodo->next;
    }
}