#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    printf("Programma che in base al processo genitore/figlio stampa una cosa diversa.\n\n");
    printf("Programma in cui il processo genitore stampa il pid del figlio - ottenuto tramite la fork() -\n");
    printf("e il processo figlio stampa 0 qualora il fork() sia andato buon fine.\n");
    printf("I due processi hanno un messaggio personalizzato grazie al controllo del pid.\n\n");

    pid_t pid = fork();

    if(pid>0){
        printf("[genitore] Stampo %d ovvero il pid di mio figlio\n", pid);
    } else if(pid==0){
        printf("[figlio] Stampo %d perche' tutto e' andato bene\n", pid);
    } else if(pid<0){
        fprintf(stderr, "Errore, qualcosa e' andato storto\n");
        exit(1);
    }

    return 0;
}