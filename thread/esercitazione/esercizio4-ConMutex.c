#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>
#include<time.h>

#define RESET "\033[0m" //reset colore
#define MAGENTA "\033[35m"
#define GREEN    "\033[32m" // Verde
#define YELLOW    "\033[33m" // Giallo

#define NUM 5

pthread_t fil[NUM];
pthread_mutex_t forks[NUM]; //vettore con all'interno i proprietari delle forchette

void* routine(void* arg){
    int filosofo = *((int*) arg);

    while(1){
        pthread_mutex_lock(&forks[filosofo%NUM]);
        //printf("[%d] ho preso la forchetta sinistra\n", (filosofo%NUM));

        pthread_mutex_lock(&forks[(filosofo+1)%NUM]);
        //printf("[%d] ho preso la forchetta destra\n", (filosofo%NUM));
        
        printf(GREEN "[%d] sto mangiando...\n", (filosofo%NUM));
        usleep(1000*(rand()%100));
        
        pthread_mutex_unlock(&forks[(filosofo+1)%NUM]);
        //printf("[%d] ho lasciato la forchetta destra\n", (filosofo%NUM));
        
        printf(YELLOW "[%d] sto pensando...\n", (filosofo%5));
        usleep(1000*(rand()%100));

        pthread_mutex_unlock(&forks[filosofo%NUM]);
        //printf("[%d] ho lasciato la forchetta sinistra\n", (filosofo%NUM));
        
        usleep(10000*(rand()%100));
    }    
    return NULL;
}

// Funzione di gestione del segnale
void handle_sigint(int sig) {
    printf("\n" RESET, sig);
    exit(0); // Esci dal programma
}

int main(){

    // Registra la funzione di gestione del segnale
    signal(SIGINT, handle_sigint);

    printf(MAGENTA "Programma che implementa il problema dei filosofi a cena con i threads, utilizzando solo le mutex\n\n");

    srand(time(NULL));

    for(int i=0; i<NUM; i++){
        if(pthread_create(fil+i, NULL, routine, (void*)&i) != 0){
            fprintf(stderr, "Errore creazione threads\n");
            exit(1);
        }
    }
    for(int i=0; i<NUM; i++){
        pthread_join(*(fil+i), NULL);
    }

    return 0;
}