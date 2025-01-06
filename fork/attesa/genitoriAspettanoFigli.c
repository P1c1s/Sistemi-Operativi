#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

    printf("Programma dove i genitori aspettano i loro figli.\n\n");
    
    int pid = fork();
    pid = fork();
    pid = fork();

    if(pid>0){
        waitpid(pid, NULL, 0);
        printf("[PID %d] Sono il processo padre di %d e l'ho aspettato\n", getpid(), pid);
    }
    else if(pid==0)
        printf("[PID %d] Sono il processo figlio di %d e ho la precedenza\n", getpid(), getppid());
    else if(pid==-1)
        fprintf(stderr, "Errore fork\n");

    return 0;

}
