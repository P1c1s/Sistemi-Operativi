#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    printf("Programma che in base al processo genitore/figlio stampa una cosa diversa.\n\n");
    int pid = fork();

    if(pid>0){
        printf("[genitore] Stampo il pid di mio figlio -> %d\n", pid);
    } else if(pid==0){
        printf("[figlio] Stampo %d perche' tutto e' andato bene\n", pid);
    } else if(pid<0){
        fprintf(stderr, "Errore, qualcosa e' andato storto\n");
        exit(1);
    }

    return 0;
}