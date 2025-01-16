#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(){

    printf("Programma che crea un figlio che chiude lo standard output\n");
    printf("e sfrutta lo standard error.\n\n");

    pid_t pid = fork();

    if(pid>0){
        wait(NULL);
        printf("Sono il genitore e il mio standard output è ancora attivo\n");
    }
    else if(pid==0){
        printf("Sono il figlio e ho chiuso lo standard output\n");
        close(STDOUT_FILENO);
        printf("Questo messaggio non verrà visualizzato.");
        
        if(close(STDOUT_FILENO)==-1){
            fprintf(stderr, "Errore, qualcuno ha chiuso lo standard output\n\n");
            exit(1);
        }
    }
    else if(pid<0){
        fprintf(stderr, "Errore fork\n");
        exit(1);
    }
    return 0;
}