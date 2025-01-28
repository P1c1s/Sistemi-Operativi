#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

#define numFil 5

#define RESET   "\033[0m"  // Reset del colore
#define RED     "\033[31m" // Rosso
#define GREEN   "\033[32m" // Verde
#define YELLOW  "\033[33m" // Giallo
#define BLUE    "\033[34m" // Blu
#define MAGENTA "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano
#define WHITE   "\033[37m" // Bianco

void* filosofare(void*);

pthread_t filosofi[numFil];
pthread_mutex_t forchette[numFil];               //le forchette sono delle risorse condiviseq 
int indice = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(){

    srand(time(NULL));

    for(int i=0; i<numFil; i++){
        pthread_mutex_init(forchette+i, NULL);          //inizializza le mutex
    }

    for(int i=0; i<numFil; i++){
        pthread_create(filosofi+i, NULL, filosofare, NULL); //crea i thread
    }

    for(int i=0; i<numFil; i++){
        pthread_join(*(filosofi+i), NULL);
    }

    for(int i=0; i<numFil; i++){
        pthread_mutex_destroy(forchette+i);             //libera le mutex
    }
    pthread_mutex_destroy(&mutex);

    return 0;
}

void* filosofare(void* arg){
    pthread_mutex_lock(&mutex);
        int indexFilosofo = indice;
        indice++;
    pthread_mutex_unlock(&mutex);

    
    while(1){

        printf(CYAN "Filosofo %d sta pensando\n", indexFilosofo+1);
        usleep(rand()%100 * 10000);

        pthread_mutex_lock(forchette + indexFilosofo);
        pthread_mutex_lock(forchette + (indexFilosofo+numFil-1)%numFil);

        printf(GREEN "Filosofo %d sta mangiando\n", indexFilosofo+1);
        usleep(rand()%100 * 10000);
        printf(YELLOW "Filosofo %d ha finito di mangiare\n", indexFilosofo+1);


        pthread_mutex_unlock(forchette + indexFilosofo);
        pthread_mutex_unlock(forchette + (indexFilosofo+numFil-1)%numFil);

        usleep(rand()%100 * 10000);
    }
    return NULL;
}