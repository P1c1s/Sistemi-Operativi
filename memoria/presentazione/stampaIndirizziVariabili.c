#include <stdio.h>
#include <stdlib.h>

int main(){

    printf("Programma che stampa gli indirizzi di memoria di alcune variabili.\n\n");

    //Variabili
    int intero = 1;
    float decimale = 32.34;
    char carattere = 'Q';
    char stringa[10] = "parola\0";

    //Puntatori
    int* puntatoreIntero = &intero;
    float* puntatoreDecimale = &decimale;
    char* puntatoreCarattere = &carattere;
    char* puntatoreStringa = stringa;

    printf("[%p] Intero con valore %d\n", &intero, intero);
    printf("[%p] Float con valore %f\n", &decimale, decimale);
    printf("[%p] Carattere con valore %c\n", &carattere, carattere);
    printf("[%p] Stringa con valore %s\n", &stringa, stringa);
    printf("[%p] Puntatore a indirizzo %p a intero %d\n", &puntatoreIntero, &(*puntatoreIntero), *puntatoreIntero);
    printf("[%p] Puntatore a indirizzo %p a float %f\n", &puntatoreDecimale, &(*puntatoreDecimale), *puntatoreDecimale);
    printf("[%p] Puntatore a indirizzo %p a carattere %c\n", &puntatoreCarattere, &(*puntatoreCarattere), *puntatoreCarattere);
    printf("[%p] Puntatore a indirizzo %p a stringa solo primo carattere %c\n", &puntatoreStringa, &(*puntatoreCarattere), *puntatoreStringa);

    return 0;
    
}


