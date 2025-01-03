#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    printf("Programma che esegue n fork, ogni fork da vita ad un nuovo processo figlio\n");
    printf("che a sua volta da vita ad un nuovi processi per via delle n-1 fork.\n\n");

    int pid1 = fork();
    int pid2 = fork();
    int pid3 = fork();    

    if(pid1>0)
        printf("Ciao dal genitore [pid %d]\n", getpid()); 
    else if(pid1==0)
        printf("Ciao dal figlio [pid %d]\n", getpid()); 

    return 0;

}
