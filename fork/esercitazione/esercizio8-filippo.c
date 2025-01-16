#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(){

    printf("Programma che crea due processi figli e collega lo standard ");
    printf("output di uno allo standard input dell'altro\n\n");

    //pipe[0] informazione di lettura, pipe[1] informazione di scrittura
    int pipefd[2];
    
    if(pipe(pipefd) == -1){
        fprintf(stderr, "Errore nella pipe\n");
        exit(1);
    }
    
    pid_t pid = fork();

    if(pid>0){
        //il padre aspetta che il figlio gli mandi il messaggio
        printf("s1 g");
        wait(NULL);
        printf("s2 g");
        char bufferF[100];
        //lettura dalla pipe del messaggio del figlio
        read(pipefd[0], bufferF, sizeof(bufferF));

        int scrP = write(pipefd[1], "Ciao figlio, qui tutto bene.\n", sizeof("Ciao figlio, qui tutto bene."));
        
        if(scrP<0){
            fprintf(stderr, "Errore nella write\n");
            exit(1);
        }
    }
    else if(pid==0){
        //il figlio scrive il messaggio al padre
        int scrF = write(pipefd[1], "Ciao papa', tutto bene?", sizeof("Ciao papa', tutto bene?"));
        
        if(scrF<0){
            fprintf(stderr, "Errore nella write\n");
            exit(1);
        }

        printf("s1 f\n");
        waitpid(getppid(), NULL, 0);
        printf("s2 f\n");

        char bufferP[100];
        read(pipefd[0], bufferP, sizeof(bufferP));
        
        close(pipefd[0]);
        close(pipefd[1]);
    }

    else if(pid<0){
        fprintf(stderr, "Errore fork\n");
        exit(1);
    }
    return 0;
}