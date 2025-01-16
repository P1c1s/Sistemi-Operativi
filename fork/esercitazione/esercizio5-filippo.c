#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    
    printf("Programma dove il genitore aspetta il figlio e viceversa.\n\n");

    pid_t pid = fork();
    
    //prima il figlio poi il padre
    if(pid>0){
        printf("Sono il genitore e aspetto mio figlio...\n");
        wait(NULL);
        printf("Sono il genitore e ora è il mio turno\n\n");
    }
    else if(pid==0){
        printf("Sono il figlio ed è il mio turno\n");
    }
    else if(pid<0){
        fprintf(stderr, "Errore fork\n");
        exit(1);
    }

    //prima il padre poi il figlio (decommenta questa parte e commenta quella sopra)

    // if(pid>0){
    //     printf("Sono il genitore e stavolta prima tocca a me\n");
    // }
    // else if(pid==0){
    //     wait(NULL);
    //     printf("Sono il figlio e ora che ha finito mio padre è il mio turno\n");
    // }
    // else if(pid<0){
    //     fprintf(stderr, "Errore fork\n");
    //     exit(1);
    // }

    // return 0;
}