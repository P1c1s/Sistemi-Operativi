#include <stdio.h>
#include <stdlib.h>

int main(){

    printf("Programma che stampa gli indirizzi adiacenti di memoria.\n\n");

    char stringa[7] = "stringa";

    for(int i=0; i<7; i++)
        printf("[%p] %c\n", &stringa[i], stringa[i]);

    return 0;
    
}


