#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    printf("Programma che in base al processo genitore/figlio stampa una cosa diversa.\n");
    printf("|  PID  | tipo di processo |\n");
    printf("----------------------------\n");
    printf("|  num  |     genitore     |\n");
    printf("|   0   |      figlio      |\n\n");

    int pid = fork();
    printf("[PID %d] \n", pid);

    return 0;
}