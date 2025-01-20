#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<sys/mman.h>

#define DIM 5

//funzione che libera la memoria occupata e disattiva la mappatura
int myFree(void* punt, int dimensione){
    return munmap(punt, dimensione*sizeof(int));
}

//funzione che mappa una porzione di memoria anonima
void* myMalloc(int dim){
    return mmap(NULL, dim*sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
}

int main(){

    printf("Programma che implementa la malloc() e la free() manualmente\n\n");

    int* vec = (int*)myMalloc(sizeof(DIM));

    if(vec == MAP_FAILED){
        fprintf(stderr, "Errore mappatura memoria");
        exit(1);
    }

    printf("Indirizzo di memoria mappato: %p\n", vec);

    printf("Riempi il tuo vettore:\n");
    for (int i=0; i<DIM; i++){
        scanf("%d\n", &vec[i]);
    }

    printf("Ecco il tuo vettore: ");
    for (int i=0; i<DIM; i++){
        printf("[%d]", vec[i]);
    }
    printf("\n");
    
    if(myFree(vec, DIM) == -1){
        fprintf(stderr, "Errore nel liberare la memoria\n");
        exit(1);
    }
    else
        printf("Memoria liberata!\n");
    return 0;
}