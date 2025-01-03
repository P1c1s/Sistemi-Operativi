#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    int pid = fork();

    if(pid>0){
        wait(NULL);
        printf("[genitore] Arrivederci dal processo -> %d\n", getpid());
    }
    else if(pid==0)
        printf("[figlio] Buon giorno dal processo -> %d\n", getpid());
    else if(pid==-1)
        fprintf(stderr, "Errore fork\n");

    return 0;

}
