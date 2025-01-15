#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define DIM 10
#define RESET   "\033[0m"  // Reset del colore
#define RED     "\033[31m" // Rosso
#define GREEN   "\033[32m" // Verde
#define YELLOW  "\033[33m" // Giallo
#define BLUE    "\033[34m" // Blu
#define MAGENTA "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano
#define WHITE   "\033[37m" // Bianco
pthread_mutex_t mutex;

typedef struct Pila{
    int vettore[DIM];
    int indice;
}Pila;

void stampa(Pila* pila, char* tipo){    
    printf("%s [ ", tipo);
    for(int i=0; i<pila->indice; i++)
        printf("%d ", pila->vettore[i]);
    printf("]\n");
}

// Produttore
void* produttore(void* arg) {
    Pila* pila = (Pila*)arg;
    while(1){
        usleep(10000*(rand()%100));
        pthread_mutex_lock(&mutex); // Acquisisce il mutex
        if(pila->indice < 10){
            pila->vettore[pila->indice] = rand()%100;
            pila->indice += 1;
        }
        stampa(pila, BLUE "Produttore   ");
        pthread_mutex_unlock(&mutex); // Rilascia il mutex
    }
}

// Consumatore
void* consumatore(void* arg) {
    Pila* pila = (Pila*)arg;
    while(1){
        usleep(10000*(rand()%100));
        pthread_mutex_lock(&mutex); // Acquisisce il mutex
        if(pila->indice > -1){
            pila->vettore[pila->indice] = rand()%100;
            pila->indice -= 1;
        }
        stampa(pila, MAGENTA "Consumatore  ");
        pthread_mutex_unlock(&mutex); // Rilascia il mutex
    }
}

int main(){

    Pila pila;
    pila.indice = 0;
    pthread_t tProduttore;
    pthread_t tConsumatore;

    if(pthread_create(&tProduttore, NULL, produttore, (void*)&pila) != 0){
        fprintf(stderr, "Errore thread produttore");
        exit(1);
    }
    if(pthread_create(&tConsumatore, NULL, consumatore, (void*)&pila) != 0){
        fprintf(stderr, "Errore thread consumatore");
        exit(1);
    }

    pthread_join(tProduttore, NULL);
    pthread_join(tConsumatore, NULL);
    
    return 0;

}


