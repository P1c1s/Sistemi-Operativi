#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void stampa(char* messaggio, int vettore[], int dim){
    printf("%s: [ ", messaggio);
    for(int i=0; i<dim; i++)
        printf("%d ", vettore[i]);
    printf("]\n");
}

int main(){

    printf("Programma che usa memset e memcpy.\n\n");

    int dimensione = 5;
    int* vettoreVecchio = (int*)malloc(dimensione*sizeof(int));
    int* vettoreNuovo = (int*)malloc(dimensione*sizeof(int));

    printf("Di quanti elementi vuoi che sia il vettore? ");
    scanf("%d", &dimensione);

    for(int i=0; i<dimensione; i++){
        printf("Inserisci valore: ");
        scanf("%d", vettoreVecchio+i);
    }

    memset(vettoreNuovo, 0, dimensione*sizeof(int));
    memcpy(vettoreNuovo, vettoreVecchio, dimensione*sizeof(int));

    stampa("Vecchio vettore", vettoreVecchio, dimensione);
    stampa("Nuovo vettore", vettoreNuovo, dimensione);

    return 0;
}