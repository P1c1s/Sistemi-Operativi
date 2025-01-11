#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    float uno;
    float due;
} strutturaBinaria;

void* addizione(void* arg){
    strutturaBinaria* numeri = (strutturaBinaria*)arg;
    printf("Addizione: %f\n", numeri->uno + numeri->due);
}

void* sottrazione(void* arg){
    strutturaBinaria* numeri = (strutturaBinaria*)arg;
    printf("Sottrazione: %f\n", numeri->uno - numeri->due);
}

void* moltiplicazione(void* arg){
    strutturaBinaria* numeri = (strutturaBinaria*)arg;
    printf("Moltiplicazione: %f\n", numeri->uno * numeri->due);
}

void* divisione(void* arg){
    strutturaBinaria* numeri = (strutturaBinaria*)arg;
    printf("Divisione: %f\n", numeri->uno / numeri->due);
}

int main(){

    printf("Programma che esegue dei calcoli in parallelo.\n\n");

    pthread_t threads[4];
    strutturaBinaria numeri;
    numeri.uno = 1;
    numeri.due = 2;

    pthread_create(&threads[0], NULL, addizione, (void*)&numeri);
    pthread_create(&threads[1], NULL, sottrazione, (void*)&numeri);
    pthread_create(&threads[2], NULL, moltiplicazione, (void*)&numeri);
    pthread_create(&threads[3], NULL, divisione, (void*)&numeri);

    for(int i=0; i<4; i++)
        pthread_join(threads[i], NULL);

    return 0;
}