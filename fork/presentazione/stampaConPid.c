#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    printf("Programma che stampa il pid del processo.\n\n");

    int pid = fork();

    if(pid>0)
        printf("[PID %d] genitore \n", getpid());
    else if(pid==0)
        printf("[PID %d] figlio \n", getpid());
    else if(pid==-1)
        fprintf(stderr, "ciao");

    return 0;
}