#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Programma che crea un vettore di dimenione variabile.\n\n");

    int dimensione = 0;
    int *vettore;
    
    printf("Quanti numeri vuoi inserire?\n");
    printf("valore atteso: ");
    scanf("%d", &dimensione);

    vettore = (int*)malloc(dimensione* sizeof(int));

    for(int i=0; i<dimensione; i++){
        printf("Iserisci %d° numero: ", i+1);
        scanf("%d", &vettore[i]);
    }

    printf("[ ");
    for(int i=0; i<dimensione; i++){
        printf("%d ", *(vettore+i));
    }
    printf("]");

    free(vettore);
    printf("Memoria liberata.\n");

    return 0;

}