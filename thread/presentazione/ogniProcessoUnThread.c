#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>

unsigned long idP;
unsigned long idF;

void* creazioneThreadP(void* arg){
    printf("Thread creato dal padre!\n\n");
    idP = pthread_self();
    return NULL;
}

void* creazioneThreadF(void* arg){
    printf("Thread creato dal figlio!\n\n");
    idF = pthread_self();
    return NULL;
}

int main(){

    printf("Programma che stampa un thread con il suo ID per ognuno dei due processi.\n\n");

    pid_t pid = fork();

    if(pid>0){
        wait(NULL);
        pthread_t p;   
        pthread_create(&p, NULL, creazioneThreadP, NULL);
        pthread_join(p, NULL);
        printf("[PID: %d] Sono il padre e ho lanciato il thread con ID: %lu\n", getpid(), idP);
    }
    else if(pid==0){
        pthread_t f;
        pthread_create(&f, NULL, creazioneThreadF, NULL);
        pthread_join(f, NULL);
        printf("[PID: %d] Sono il figlio e ho lanciato il thread con ID: %lu\n", getpid(), idF);
    }
    else if(pid<0){
        fprintf(stderr, "Errore fork\n");
        exit(1);
    }
    return 0;
}