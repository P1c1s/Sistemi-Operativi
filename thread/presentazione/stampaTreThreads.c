#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *stampaThreadUno(){
    while(1){
        printf("A\n");
    }
}

void *stampaThreadDue(){
    while(1){
        printf("B\n");
    }
}

void *stampaThreadTre(){
    while(1){
        printf("C\n");
    }
}

int main(){

    printf("Programma che sfrutta tre threads che stampano ognuno una lettera diversa.\n");
    printf("Notare il flusso della stampa ...\n\n");


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