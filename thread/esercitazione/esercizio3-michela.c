#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include"queue.h"

#define MAX 1000
#define RATE 10

Queue* coda;
int num;

double turnaroundtimes;
int jobsdone;

void* prodjob(void*);
void* consjob(void*);
void* jobo(void*);

void stats();

pthread_mutex_t mutex;

int main(){

    num = 0;
    turnaroundtimes = 0;
    jobsdone = 0;
    pthread_t esec, proc;
    pthread_mutex_init(&mutex, NULL);

    srand(time(NULL));

    coda = (Queue*) malloc(sizeof(Queue));
    initializeQueue(coda);

    pthread_create(&proc, NULL, prodjob, NULL);
    pthread_create(&esec, NULL, consjob, NULL);

    while(1){
        sleep(2);
        stats();
    }

    pthread_join(proc, NULL);
    pthread_join(esec, NULL);

    pthread_mutex_destroy(&mutex);
    free(coda);

    return 0;
}


void* prodjob(void* argc){
    pthread_t job[RATE];
    while(1){
        for(int i=0; i<RATE && num<MAX; i++){
            pthread_create(job+i, NULL, jobo, NULL);
        }
        for(int i=0; i<RATE && num<MAX; i++){
            pthread_join(*(job+i), NULL);
        }
        sleep(1);
    }
    return NULL;
}

void* consjob(void* argc){
    while(1){
        if(isQueueEmpty(coda) == 0){
            Process* job = dequeue(coda);

            pthread_mutex_lock(&mutex);
            num--;
            pthread_mutex_unlock(&mutex);

            gettimeofday(&(job->start), NULL);
            usleep((rand()%100) * 1000);
            gettimeofday(&(job->end), NULL);

            printf("[TID %ld] : job processato\n", job->id);
            double tempo = (job->end.tv_sec - job->start.tv_sec) + (job->end.tv_usec - job->start.tv_usec) / 1000000.0;
            printf("Tempo: %f\n", tempo);
            turnaroundtimes += ((job->end.tv_sec - job->arrival.tv_sec) + (job->end.tv_usec - job->arrival.tv_usec) / 1000000.0);
            
            pthread_mutex_lock(&mutex);
            jobsdone += 1;
            pthread_mutex_unlock(&mutex);

        }
        else{
            printf("Empty queue. Waiting...\n");
        }
        usleep((rand()%100) * 1000);
    }
    
    return NULL;
}

void* jobo(void* argc){
    Process* job = (Process*) malloc(sizeof(Process));
    job->id = (long) pthread_self();
    gettimeofday(&(job->arrival), NULL);
    
    pthread_mutex_lock(&mutex);
    num += 1;
    pthread_mutex_unlock(&mutex);

    printf("[TID %ld] : job in coda\n", job->id);
    enqueue(coda, job);
    
    return NULL;
}

void stats()
{
    printf("\nTempo di turnaruond medio\t%f\n", turnaroundtimes/jobsdone);
    printf("Numero di job nella coda\t%d\n\n", num);
}