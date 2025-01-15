#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

#define NUM 10

void* produttore(void*);
void* consumatore(void*);

void push(int*, int*, int);
int pop(int*, int*);

pthread_mutex_t mutex;

int main(){
    pthread_t prod, cons;

    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    //printf("A");
    int* pila = (int*) calloc(NUM, sizeof(int));
    int dimensione = 0;

    //printf("B");

    int** arg = (int**) malloc(2*sizeof(int*));
    arg[0] = pila;
    arg[1] = &dimensione;

    pthread_create(&prod, NULL, produttore, (void*)arg);
    pthread_create(&cons, NULL, consumatore, (void*)arg);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    free(arg);
    free(pila);
    return 0;
}

void push(int* pila, int* dimensione, int numero){
    //printf("F");
    pila[*dimensione] = numero;
    (*dimensione)++;
}

int pop(int* pila, int* dimensione){
    //printf("I");
    (*dimensione)--;
    int pippo = pila[*dimensione];
    pila[*dimensione] = 0;
    return pippo;
}


void* produttore(void* argc){
    //printf("C");
    int* pila = ((int**)argc)[0];
    int* dimensione = ((int**)argc)[1]; 
    while (1){
        //printf("D");
        if (*dimensione<10){
            //printf("E");
            int numero = rand()%100;
            pthread_mutex_lock(&mutex);
            printf("\nProdotto : %d", numero);
            push(pila, dimensione, numero);
            pthread_mutex_unlock(&mutex);
            usleep((rand()%100)*10000);
        }
    }
}

void* consumatore(void* argc){
    //printf("G");
    int* pila = ((int**)argc)[0];
    int* dimensione = ((int**)argc)[1]; 
    while(1){
        //printf("H");
        if (*dimensione>0){
            pthread_mutex_lock(&mutex);
            int numero = pop(pila, dimensione);
            printf("\nConsumato : %d ", numero);
            pthread_mutex_unlock(&mutex);
        }
        else{
            printf("\nPila vuota, in attesa... ");
        }
        usleep((rand()%100)*10000);
    }
}