#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define DIM 1000


typedef struct {
    int uno;
    int due;
    int addizione;
    int sottrazione;
    int moltiplicazione;
    float divisione;
} strutturaBinaria;

void* addizione(void* arg){
    strutturaBinaria* numeri = (strutturaBinaria*)arg;
    for(int i=0; i<DIM; i++)
        numeri[i].addizione = numeri[i].uno + numeri[i].due;
}

void* sottrazione(void* arg){
    strutturaBinaria* numeri = (strutturaBinaria*)arg;
    for(int i=0; i<DIM; i++)
        numeri[i].sottrazione = numeri[i].uno + numeri[i].due;
}

void* moltiplicazione(void* arg){
    strutturaBinaria* numeri = (strutturaBinaria*)arg;
    for(int i=0; i<DIM; i++)
        numeri[i].moltiplicazione = numeri[i].uno + numeri[i].due;
}

void* divisione(void* arg){
    strutturaBinaria* numeri = (strutturaBinaria*)arg;
    for(int i=0; i<DIM; i++)
        numeri[i].divisione = numeri[i].uno + numeri[i].due;
}

int main(){

    printf("Programma che esegue dei calcoli in parallelo.\n\n");
    
    struct timeval start, end;

    pthread_t threads[4];
    strutturaBinaria numeri[DIM];

    for(int i=0; i<DIM; i++){
        numeri[i].uno = rand()%100;
        numeri[i].due = rand()%100;
    }

    /* CALCOLO IN PARALLELO*/

    // Inizio del tempo
    gettimeofday(&start, NULL);

    pthread_create(&threads[0], NULL, addizione, (void*)&numeri);
    pthread_create(&threads[1], NULL, sottrazione, (void*)&numeri);
    pthread_create(&threads[2], NULL, moltiplicazione, (void*)&numeri);
    pthread_create(&threads[3], NULL, divisione, (void*)&numeri);

    for(int i=0; i<4; i++)
        pthread_join(threads[i], NULL);

    // Fine del tempo
    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Tempo di esecuzione: %f secondi\n", time_taken);

    /* CALCOLO NON PARALLELO*/
    
    // Inizio del tempo
    gettimeofday(&start, NULL);

    for(int i=0; i<DIM; i++)
        numeri[i].addizione = numeri[i].uno + numeri[i].due;

    for(int i=0; i<DIM; i++)
        numeri[i].sottrazione = numeri[i].uno + numeri[i].due;

    for(int i=0; i<DIM; i++)
        numeri[i].moltiplicazione = numeri[i].uno + numeri[i].due;

    for(int i=0; i<DIM; i++)
        numeri[i].divisione = numeri[i].uno + numeri[i].due;

    // Fine del tempo
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Tempo di esecuzione: %f secondi\n", time_taken);

    return 0;
}