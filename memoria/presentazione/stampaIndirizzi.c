#include <stdio.h>
#include <stdlib.h>

int main(){

    printf("Programma che stampa gli indirizzi di memoria.\n\n");

    //Variabili
    int intero = 1;
    float decimale = 32.34;
    char carattere = 'a';
    char stringa[10] = "stringa";

    //Puntatori
    int* puntatoreIntero = &intero;
    float* puntatoreDecimale = &decimale;
    char* puntatoreCarattere = &carattere;
    char* puntatoreStringa = stringa;

    printf("[%p] %d\n", &intero, intero);
    printf("[%p] %f\n", &decimale, decimale);
    printf("[%p] %c\n", &carattere, carattere);
    printf("[%p] %s\n", &stringa, stringa);
    printf("[%p] puntatore alla cella %p a intero %d\n", &puntatoreIntero, &(*puntatoreIntero), *puntatoreIntero);
    printf("[%p] puntatore alla cella %p a float %f\n", &puntatoreDecimale, &(*puntatoreDecimale), *puntatoreDecimale);
    printf("[%p] puntatore alla cella %p a carattere %c\n", &puntatoreCarattere, &(*puntatoreCarattere), *puntatoreCarattere);
    printf("[%p] puntatore a stringa %p a stringa %s\n", &puntatoreStringa, &(*puntatoreCarattere), *puntatoreStringa);

    return 0;
    
}


