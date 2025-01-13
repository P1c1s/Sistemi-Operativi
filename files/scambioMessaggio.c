#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    
    printf("Programma che usa la pipe per passare un messagio\n");
    printf("tra il processo figlio e il processo genitore.\n");
    printf("+ pipefd[0] -> lettura\n+ pipefd[1] -> scrittura\n\n");

    int pipefd[2];
    if (pipe(pipefd) == -1){
        fprintf(stderr, "Errore pipe\n");
        exit(1);
    }

    int pid = fork();

    if(pid==0){
        write(pipefd[1], "Ciao genitore, come stai?", sizeof("Ciao genitore, come stai?")); // Scrive "Messaggio" nella pipe
    }
    else if(pid>0){
        waitpid(pid, NULL, 0);
        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer)); // Legge dalla pipe
        printf("[Messaggio passato dal figlio al padre] %s\n", buffer);
        printf("[Messaggio dal padre] Bene figlio mio!\n");
        close(pipefd[0]); // Chiude il lato di lettura
        close(pipefd[1]); // Chiude il lato di scrittura
    }else if(pid<0){
        fprintf(stderr, "Errore fork\n");
        exit(1);
    }

    return 0;

}


/* ANDREBBERO MESSI MA NON MI PARE FACCIANO NULLA, MI PARE STRANO :(
close(pipefd[0]); // Chiude il lato di lettura
close(pipefd[1]); // Chiude il lato di scrittura
*/