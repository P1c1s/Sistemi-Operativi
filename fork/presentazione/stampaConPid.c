#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    printf("Programma che stampa il pid del processo.\n");

    int pid = fork();

    if(pid>0)
        printf("[genitore] %d\n", getpid());
    else if(pid==0)
        printf("[figlio] %d\n", getpid());
    else if(pid==-1)
        fprintf(stderr, "ciao");

    return 0;
}