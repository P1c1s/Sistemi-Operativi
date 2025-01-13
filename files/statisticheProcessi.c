#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    
    printf("Programma che stampa una statistica sul numero di processi totali\n");
    printf("ogni processo si include nel conteggio.\n\n");

    int capostipite = getpid();
    int numero = 0;
    //int figli = 0;

    int pipefd[2];
    if(pipe(pipefd) == -1){
        fprintf(stderr, "Errore pipe\n");
        exit(1);
    }

    int pid = fork();
    pid = fork();
    pid = fork();
    pid = fork();
    
    if(pid==0){
        numero += 1;
        write(pipefd[1], &numero, sizeof(numero)); // Scrive "Messaggio" nella pipe
    }
    else if(pid>0){
        waitpid(pid, NULL, 0);
        read(pipefd[0], &numero, sizeof(numero)); // Legge dalla pipe
        printf("[%d]\n", numero);
        numero += 1;
    }else if(pid<0){
        fprintf(stderr, "Errore fork\n");
        exit(1);
    }

    if(capostipite==getpid()){
        wait(NULL);
        printf("Genitori: %d\n", numero);
        printf("Figli: %d\n", numero);
    }

    return 0;

}