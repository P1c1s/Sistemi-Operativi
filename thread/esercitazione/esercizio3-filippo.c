#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/time.h>
#include<stdbool.h>
#include"queue.h"

#define RESET "\033[0m" //reset colore
#define RED     "\033[31m" // Rosso
#define GREEN    "\033[32m" // Verde
#define YELLOW    "\033[33m" // Giallo
#define MAGENTA  "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano

#define RATE 10 //tasso di generazione dei processi
#define MAX 100    //numero massimo di processi supportati

int num;    //numero di job generati

pthread_mutex_t mutex;
Queue* q;

int jobsDone;

double tempo;
double turnaroundTime;

/*THREAD PER L'ESECUZIONE DEI JOBS*/
void* job(void* arg){
    Process* j = (Process*)malloc(sizeof(Process)); //job da eseguire

    //inizializzo le informazioni del job
    j->id = (long) pthread_self();
    gettimeofday(&(j->arrival), NULL);

    //job generato
    pthread_mutex_lock(&mutex);
    num++;
    pthread_mutex_unlock(&mutex);

    //inserisco il job nella coda
    printf(RED "[TID %ld] Job in coda...\n" RESET, j->id);
    enqueue(q, j);
    
    return NULL;
}


/*THREAD PRODUTTORE DI JOBS -> INSERISCE I JOB NELLA CODA*/
void* produttore(void* arg){
    
    //processi da generare (array -> puntatore)
    pthread_t jobs[RATE];

    while(1){
        //genero i 10 job
        //(ATTENZIONE: questo thread potrebbe essere interrotto dagli altri -> no mutex)
        for(int i=0; i<RATE && num<MAX; i++){
            if(pthread_create(jobs+i, NULL, job, NULL) != 0){
                fprintf(stderr, "Errore creazione job\n");
                exit(1);
            }
        }
        //attendo che i threads terminino
        for(int i=0; i<RATE && i<=MAX; i++)
            pthread_join(*(jobs+i), NULL);
    
        //tempo di generazione dei threads: 1 secondo
        sleep(1);
    }
    return NULL;
}

/*THREAD CONSUMATORE DI JOBS -> ESEGUE ED ESTRAE I JOBS DALLA CODA*/
void* consumatore(void* arg){
    //variabile per il job processato
    Process* jobdone = (Process*)malloc(sizeof(Process));

    while(1){
        //coda vuota
        if(isQueueEmpty(q))
            printf(YELLOW "Ancora nessun elemento in coda, attendere...\n" RESET);
            //inserire qui una exit(1) per resettare il colore
        else{
            //estraggo dalla coda il job processato
            jobdone = dequeue(q);
            
            //job estratto
            pthread_mutex_lock(&mutex);
            num--;
            pthread_mutex_unlock(&mutex);


            /*CALCOLO I PARAMETRI RICHIESTI*/

            //1) TEMPO DI ESECUZIONE:
            gettimeofday(&(jobdone->start), NULL);
            usleep(1000*(rand()%100));
            gettimeofday(&(jobdone->end), NULL);
            
            printf(GREEN "[TID %ld] Job processato!\n" RESET, jobdone->id);

            double tempoInSec = ((jobdone->end.tv_sec) - (jobdone->start.tv_sec));
            double tempoInMicroSec = ((jobdone->end.tv_usec) - (jobdone->start.tv_usec));

            tempo = (tempoInSec + tempoInMicroSec) / 1000000.0;

            printf(GREEN "Tempo di processamento: %f\n" RESET, tempo);


            //2) TURNAROUND TOTALE
            double turnaroundTimeInSec = ((jobdone->end.tv_sec) - (jobdone->arrival.tv_sec));
            double turnaroundTimeInMicroSec = ((jobdone->end.tv_usec) - (jobdone->arrival.tv_usec));            
        
            turnaroundTime += (((turnaroundTimeInSec) + (turnaroundTimeInMicroSec)) / 1000000.0);    

            //incremento il totale di job eseguiti
            pthread_mutex_lock(&mutex);
            jobsDone++;
            pthread_mutex_unlock(&mutex); 
        }
        usleep(1000*(rand()%100));
    }
    return NULL;
}

/*STATISTICHE*/
void stats(){
    double turnaroundTimeMedio = turnaroundTime/jobsDone;
    
    printf(CYAN "Turnaround Time medio: %f\n"RESET , turnaroundTimeMedio);
    printf(CYAN "Jobs in coda: %d\n\n"RESET , num);
}

int main(){
    
    printf(MAGENTA "Programma che simula il funzionamento dello scheduler di un sistema operativo\n\n" RESET);

    //inizializzo la coda
    q = (Queue*)malloc(sizeof(Queue));
    initializeQueue(q);

    num = 0;    //ancora nessun job generato

    srand(time(NULL));

    //thread che genera processi (10 al secondo)
    pthread_t prod;
    if(pthread_create(&prod, NULL, produttore, NULL) != 0){
        fprintf(stderr, "Errore creazione produttore");
        exit(1);
    }

    pthread_t cons;
    if(pthread_create(&cons, NULL, consumatore, NULL) != 0){
        fprintf(stderr, "Errore creazione consumatore\n");
        exit(1);
    }

    //produco le statistiche
    while(1){
        stats();
        sleep(2);
    }

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);


    return 0;
}
