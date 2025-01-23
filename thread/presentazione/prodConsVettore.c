#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#include<sys/mman.h>
#include<string.h>

#define DIM 10

int i;

pthread_mutex_t mutex;

void* produttore(void* arg){
    int* vec = (int*) arg;    

    while(1){
        pthread_mutex_lock(&mutex);
        i = rand()%10;
        vec[i] = rand()%100;
        printf("Produttore: [%d] in %da posizione\n", vec[i], i+1);
        
        for(int i=0; i<DIM; i++){
            printf("[%d]", vec[i]);
        }
        printf("\n\n");
        
        pthread_mutex_unlock(&mutex);
        
        usleep(rand()%100*20000);
    }
    return NULL;  
}

void* consumatore(void* arg){
    int* vec = (int*) arg;

    while(1){
        pthread_mutex_lock(&mutex);
        i = rand()%10;
        vec[i] = 0;
        printf("Consumatore: [%d] in %da posizione\n", vec[i], i+1);
        
        for(int i=0; i<DIM; i++){
            printf("[%d]", vec[i]);
        }
        printf("\n\n");
                
        pthread_mutex_unlock(&mutex);
        
        usleep(rand()%100*20000);
    }
    return NULL;
}

int main(){

    srand(time(NULL));

    printf("\nProgramma con due thread che condividono lo stesso vettore\n\n");

    int* vec = mmap(NULL, DIM*sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    
    memset(vec, 0, DIM*sizeof(int));

    printf("Vettore iniziale:");
    for(int i=0; i<DIM; i++){
        printf("[%d]", vec[i]);
    }
    printf("\n\n");

    pthread_t prod;
    if(pthread_create(&prod, NULL, produttore, (void*) vec) != 0){
        fprintf(stderr, "Errore creazione produttore\n");
        exit(1);
    }    
    pthread_t cons;
    if(pthread_create(&cons, NULL, consumatore, (void*) vec) != 0){
        fprintf(stderr, "Errore creazione consumatore\n");
        exit(1);
    }

    pthread_join(prod, NULL);   //se invertiti, segmentation fault    
    pthread_join(cons, NULL);

    return 0;
}