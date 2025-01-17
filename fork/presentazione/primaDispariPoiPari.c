#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){

    printf("Programma in cui il processo genitore stampa numeri dispari\n");
    printf("mentre il processo figlio stampa numeri pari.\n\n");

    pid_t pidG = getpid();
    pid_t pid = fork();

    for (int i=1; i<=10; i++){
        if(pid>0 && i%2 != 0){
            printf("[genitore] -> %d\n", i);
        }
        else if(pid==0 && i%2 == 0){
            printf("[figlio] -> %d\n", i);
            wait(&pidG);
        }
        else if(pid<0){
            fprintf(stderr, "Errore fork\n");
            exit(1);
        }
    }
    return 0;
}