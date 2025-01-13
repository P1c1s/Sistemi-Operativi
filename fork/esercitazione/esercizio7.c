#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    
    printf("Programma che crea un figlio che chiude lo standard outpt\n");
    printf("e sfrutta lo standard error.\n\n");

    int pid = fork();

    if(pid==0){
        close(STDOUT_FILENO); //Chiude standard output
        printf("Qualcosa che non sarà mai stampato.\n");
        if(close(STDOUT_FILENO)==-1) //Controlla se lo stream sia chiuso oppure no
            fprintf(stderr, "Errore, standard output chiuso.\n");
    }else if(pid>0){
        wait(NULL);
        printf("Mio figlio ha chiuso lo stream video.\n");
    }else if(pid<0){
        fprintf(stderr, "Fork fallita.\n");
        exit(1);
    }

    return 0;
}