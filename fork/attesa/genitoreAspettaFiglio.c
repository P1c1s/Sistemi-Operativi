#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

    printf("Programma dove il genitore aspetta il figlio.\n\n");
    
    int pid = fork();

    if(pid>0){
        wait(NULL);
        printf("[PID %d] Arrivederci dal processo genitore \n", getpid());
    }
    else if(pid==0)
        printf("[PID %d] Buon giorno dal processo figlio \n", getpid());
    else if(pid==-1)
        fprintf(stderr, "Errore fork\n");

    return 0;

}
