#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>    //wait system call

int main(){

    int pid = fork();

    if(pid>0){
        wait(NULL); //aspetta che il figlio termini
        printf("GENITORE: Goodbye\n");
    }
    else if(pid==0){
        printf("FIGLIO: Hello\n");
    }
    else if(pid<0){
        fprintf(stderr, "Errore fork\n");
        exit(1);
    }
}