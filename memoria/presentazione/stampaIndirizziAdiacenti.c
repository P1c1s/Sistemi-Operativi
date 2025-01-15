#include <stdio.h>
#include <stdlib.h>

int main(){

    printf("Programma che stampa gli indirizzi delle celle di un vettore di caratteri.\n");
    printf("[Nota] Sono indirizzi di memoria adiacenti.\n\n");

    char stringa[7] = "stringa";

    for(int i=0; i<7; i++)
        printf("[%p] %c\n", &stringa[i], stringa[i]);

    return 0;
    
}


