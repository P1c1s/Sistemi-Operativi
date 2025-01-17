#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    printf("Programma in cui il processo genitore stampa il pid del figlio - ottenuto tramite la fork() -\n");
    printf("e il processo figlio stampa 0 qualora il fork() sia andato buon fine.\n\n");
    printf("|  PID  | tipo di processo |\n");
    printf("----------------------------\n");
    printf("|   n   |     genitore     |\n");
    printf("|   0   |      figlio      |\n");
    printf("|  -1   |      errore      |\n\n");

    pid_t pid = fork();
    printf("[PID %d] \n", pid);

    return 0;
}