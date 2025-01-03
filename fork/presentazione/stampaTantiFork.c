#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    printf("Programma che esegue n fork, ogni fork da vita ad un nuovo processo figlio\n");
    printf("che a sua volta da vita ad un nuovi processi per via delle n-1 fork.\n\n");

    int pid = fork();
    pid = fork();
    pid = fork();    

    if(pid>0)
        printf("[pid %d] Sono un processo gentiore che ha creato il processo figlio %d\n", getpid(), pid); 
    else if(pid==0)
        printf("[pid %d] Sono un processo dal figlio genrato dal processo %d\n", getpid(), getppid()); 

    return 0;

}
