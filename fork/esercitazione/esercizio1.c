#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    printf("Programma che stampa il valore della variabile x prima e dopo\n");
    printf("il suo incremento che avviene dopo la fork.\n\n");
    
    int x = 100;
    int pid = fork();

    if(pid>0){
        printf("[genitore] Stampa del valore di x: %d\n", x);
    } else if(pid==0){
        printf("[figlio] Stampa del valore di x: %d\n", x);
    } else if(pid<0){
        fprintf(stderr, "Errore fork\n");
        exit(1);
    }

    x += 1;

    if(pid>0){
        printf("[genitore] Stampa del valore di x: %d\n", x);
    } else if(pid==0){
        printf("[figlio] Stampa del valore di x: %d\n", x);
    } else if(pid<0){
        fprintf(stderr, "Errore fork\n");
        exit(1);
    }

    return 0;
}