#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    printf("Programma che in base al processo genitore/figlio stampa una cosa diversa.\n");
    printf("| pid | processo |\n");
    printf("------------------\n");
    printf("| num | genitore |\n");
    printf("|  0  |  figlio  |\n\n");

    int pid = fork();
    printf("[%d] Stampa del valore di x: %d\n", pid, x);

    return 0;
}