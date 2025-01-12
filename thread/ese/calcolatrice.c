#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define DIM 10
#define RESET   "\033[0m"  // Reset del colore
#define RED     "\033[31m" // Rosso
#define GREEN   "\033[32m" // Verde
#define YELLOW  "\033[33m" // Giallo
#define BLUE    "\033[34m" // Blu
#define MAGENTA "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano
#define WHITE   "\033[37m" // Bianco

typedef struct {
    float uno;
    float due;
} strutturaBinaria;

void* addizione(void* arg){
    strutturaBinaria* numeri = (strutturaBinaria*)arg;
    for(int i=0; i<DIM; i++)
        printf(RED "[Addizione] %d+%d=%d\n", (int)numeri[i].uno, (int)numeri[i].due, (int)(numeri[i].uno + numeri[i].due));
}

void* sottrazione(void* arg){
    strutturaBinaria* numeri = (strutturaBinaria*)arg;
    for(int i=0; i<DIM; i++)
        printf(GREEN "[Sottrazione] %d-%d=%d\n", (int)numeri[i].uno, (int)numeri[i].due, (int)(numeri[i].uno - numeri[i].due));
}

void* moltiplicazione(void* arg){
    strutturaBinaria* numeri = (strutturaBinaria*)arg;
    for(int i=0; i<DIM; i++)
        printf(YELLOW "[Moltiplicazione] %dx%d=%d\n", (int)numeri[i].uno, (int)numeri[i].due, (int)(numeri[i].uno * numeri[i].due));
}

void* divisione(void* arg){
    strutturaBinaria* numeri = (strutturaBinaria*)arg;
    for(int i=0; i<DIM; i++)
        printf(BLUE "[Divisione] %d/%d=%f\n", (int)numeri[i].uno, (int)numeri[i].due, (numeri[i].uno / numeri[i].due));
}


int main(){

    printf("Programma che esegue dei calcoli in parallelo.\n\n");

    pthread_t threads[4];
    strutturaBinaria numeri[DIM];

    for(int i=0; i<DIM; i++){
        numeri[i].uno = rand()%100;
        numeri[i].due = rand()%100;
    }

    pthread_create(&threads[0], NULL, addizione, (void*)&numeri);
    pthread_create(&threads[1], NULL, sottrazione, (void*)&numeri);
    pthread_create(&threads[2], NULL, moltiplicazione, (void*)&numeri);
    pthread_create(&threads[3], NULL, divisione, (void*)&numeri);

    for(int i=0; i<4; i++)
        pthread_join(threads[i], NULL);

    return 0;
}