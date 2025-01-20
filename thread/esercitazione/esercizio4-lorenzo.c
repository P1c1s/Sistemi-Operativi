#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define RESET   "\033[0m"  // Reset del colore
#define RED     "\033[31m" // Rosso
#define GREEN   "\033[32m" // Verde
#define YELLOW  "\033[33m" // Giallo
#define BLUE    "\033[34m" // Blu
#define MAGENTA "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano
#define WHITE   "\033[37m" // Bianco

pthread_mutex_t mutex;
pthread_t filosofi[5];
int forchette[5] = {0, 0 , 0 , 0, 0};

void* prova(void* arg){
    int filosofo = *((int*)arg);
    while(1){
        if(forchette[(filosofo+4)%5] == 0 && forchette[filosofo] == 0){
            printf(GREEN "Filosofo %d sta mangiando\n", filosofo+1);
            pthread_mutex_lock(&mutex);
            forchette[(filosofo+4)%5] = 1; // forchetta sinistra
            forchette[filosofo] = 1; // forchetta destra
            pthread_mutex_unlock(&mutex);
            usleep(1000*100*((rand()%100)+1));
            pthread_mutex_lock(&mutex);
            printf(CYAN "Filosofo %d ha finito di mangiare\n", filosofo+1);
            forchette[(filosofo+4)%5] = 0; // forchetta sinistra
            forchette[filosofo] = 0; // forchetta destra
            pthread_mutex_unlock(&mutex);
        }else
            printf(YELLOW "Filosofo %d sta pensando\n", filosofo+1);           
        usleep(1000*100*((rand()%100)+1));     
    }  
    return NULL;
}

int main(){
    printf("Programma che implementa il problema concettuale dei filosofi.\n\n");
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    for(int i=0; i<5; i++){
        pthread_create(&filosofi[i], NULL, prova, (void*)&i);
        usleep(100*(rand()%100));
    }

    for(int i = 0; i<5; i++)
        pthread_join(filosofi[i], NULL);


    pthread_mutex_destroy(&mutex);

    return 0;
}