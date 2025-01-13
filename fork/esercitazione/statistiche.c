#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    printf("Programma che stampa una statistica sul numero di processi totali.\n\n");

    int capostipite = getpid();
    int genitori = 0;
    int figli = 0;

    int pid = fork();
    pid = fork();
    pid = fork();
    pid = fork();

    if(pid>0){
        genitori += 1;
    }else if(pid==0){
        figli += 1;
    }else if(pid<0)
        fprintf(stderr, "Errore fork.\n");

    if(capostipite==getpid()){
        wait(NULL);
        printf("Genitori: %d\n", genitori);
        printf("Figli: %d\n", figli);
    }

    return 0;

}