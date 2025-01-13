#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#define DIM 3

void* my_malloc(int dimensione){
    // Mappa la memoria anonima
    return mmap(NULL, dimensione * sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
}

int my_free(void* puntatore, int dimensione){
    // Disattiva la mappatura
    return munmap(puntatore, dimensione * sizeof(int));
}

int main(){

    printf("Programma che fa ...\n\n");

    int* vettore = (int*) my_malloc(DIM);
    
    if(vettore == MAP_FAILED){
        fprintf(stderr, "Errore nella mappatura della memoria");
        return 1;
    }

    printf("%p\n", vettore);

    for(int i = 0; i < DIM; i++){
        printf("Inserisci il %d valore:\t", i + 1);
        scanf("%d", vettore + i);
    }

    printf("\nValori inseriti:\n");
    for(int i = 0; i < DIM; i++){
        printf("%d\n", *(vettore + i));
    }

    if(my_free(vettore, DIM) == -1){
        fprintf(stderr, "Errore nel disattivare la mappatura");
        return 1;
    }

    return 0;

}

