#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include"queue.h"

#define MAX 1000
#define RATE 10

Queue* coda;
int num;

void* prodjob(void*);
void* consjob(void*);
void* jobo(void*);

pthread_mutex_t mutex;

int main(){

    num = 0;
    pthread_t esec, proc;
    pthread_mutex_init(&mutex, NULL);

    srand(time(NULL));

    coda = (Queue*) malloc(sizeof(Queue));
    initializeQueue(coda);

    pthread_create(&proc, NULL, prodjob, NULL);
    pthread_create(&esec, NULL, consjob, NULL);

    pthread_join(proc, NULL);
    pthread_join(esec, NULL);

    pthread_mutex_destroy(&mutex);
    free(coda);

    return 0;
}


void* prodjob(void* argc){
    pthread_t job;
    while(1){
        pthread_mutex_lock(&mutex);
        for(int i=0; i<RATE && i<MAX; i++){
            pthread_create(&job, NULL, jobo, NULL);
            pthread_join(job, NULL);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void* consjob(void* argc){
    while(1){
        pthread_mutex_lock(&mutex);
        Process* job = dequeue(coda);
        gettimeofday(&(job->start), NULL);
        usleep((rand()%100) * 1000);
        gettimeofday(&(job->end), NULL);

        printf("[TI %ld] : job processato\n", job->id);
        double tempo = (job->end.tv_sec - job->start.tv_sec) + (job->end.tv_usec - job->start.tv_usec) / 1000000.0;
        printf("Tempo: %f\n", tempo);
    }
    pthread_mutex_unlock(&mutex);
    sleep(1);
    return NULL;
}

void* jobo(void* argc){
    Process* job = (Process*) malloc(sizeof(Process));
    job->id = (long) pthread_self();
    gettimeofday(&(job->arrival), NULL);
    num += 1;

    printf("[TID %ld] : job in coda\n", job->id);
    enqueue(coda, job);
    
    return NULL;
}