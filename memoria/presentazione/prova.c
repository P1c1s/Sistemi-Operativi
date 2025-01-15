#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    printf("Programma che stampa gli indirizzi di memoria.\n\n");

    for(int i=0; i<10; i++){
        int* intero = (int*)malloc(sizeof(int));
        *intero = rand()%100;
        printf("%p %d %p\n", &intero, *intero, &(*intero));
        //free(intero);        
    }

    return 0;
}


