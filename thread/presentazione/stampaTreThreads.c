#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define RESET   "\033[0m"  // Reset del colore
#define RED     "\033[31m" // Rosso
#define GREEN   "\033[32m" // Verde
#define YELLOW  "\033[33m" // Giallo
#define BLUE    "\033[34m" // Blu
#define MAGENTA "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano
#define WHITE   "\033[37m" // Bianco

void* stampaThreadUno(){
    while(1){
        printf(RED "A\n" RESET);
    }
}

void* stampaThreadDue(){
    while(1){
        printf(GREEN "B\n" RESET);
    }
}

void* stampaThreadTre(){
    while(1){
        printf(BLUE "C\n" RESET);
    }
}

int main(){

    printf("Programma che sfrutta tre threads che stampano ognuno una lettera diversa.\n");
    printf("Notare il flusso della stampa ...\n\n");

    sleep(4);

    pthread_t threadUno;
    pthread_t threadDue;
    pthread_t threadTre;

    pthread_create(&threadUno, NULL, stampaThreadUno, NULL);
    pthread_create(&threadDue, NULL, stampaThreadDue, NULL);
    pthread_create(&threadDue, NULL, stampaThreadTre, NULL);

    pthread_join(threadUno, NULL);
    pthread_join(threadDue, NULL);
    pthread_join(threadTre, NULL);

    return 0;        
}
