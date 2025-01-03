#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHILDREN 5 // Numero di processi figli da creare

int main() {

    printf("Programma che crea più processi figli che contano fino a un numero specificato,\n");
    printf("ogni processo figlio stampa il proprio PID e il numero che sta contando.\n\n");
    int pids[NUM_CHILDREN];

    for(int i=0; i<NUM_CHILDREN; i++){
        pids[i] = fork(); // Creazione di un nuovo processo
        if(pids[i]<0){
            perror("Errore nella creazione del processo");
            exit(EXIT_FAILURE);
        }else if(pids[i]==0){
            // Questo è il processo figlio
            printf("Processo figlio %d: PID = %d, conto fino a 5...\n", i + 1, getpid());
            for (int j= 1; j<=5; j++) {
                printf("Processo figlio %d: %d\n", i + 1, j);
                sleep(1); // Pausa di 1 secondo
            }
            exit(0); // Terminare il processo figlio
        }
    }

    // Questo è il processo padre
    for(int i=0; i<NUM_CHILDREN; i++){
        wait(NULL); // Attendere la terminazione di ogni processo figlio
    }

    printf("Tutti i processi figli sono terminati.\n");
    return 0;
}
