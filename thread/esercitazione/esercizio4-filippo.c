#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>
#include<time.h>

#define NUM 5

#define RESET "\033[0m" //reset colore
#define RED     "\033[31m" // Rosso
#define BLUE    "\033[32m" // Blu
#define MAGENTA  "\033[35m" // Magenta

pthread_t fil[NUM];  //filosofi

pthread_mutex_t mutex;

int forcs[NUM];  //forchetta da scambiarsi

int quanteForcs;

void* routine(void* arg){    
    
    int id;

    //assegno un id ai threads in base al loro TID e alla loro posizione in fil[]
    for(int i=0; i<NUM; i++){
        if(pthread_self() == fil[i])
            id = i;
    }   
    while(1){  
        /*PRENDO LA/E FORCHETTA/E*/
        
        //*ogni filosofo può prendere la forchetta alla sua sinistra, con indice di
        //forcs[] pari all'id dello stesso filosofo, oppure quella alla sua destra,
        //con indice di forcs[] pari all'id del filosofo + 1*

        // *per convenzione, i filosofi prendono prima la forchetta a sinistra, se libera*

        int dueF = 0;

        //forchetta a sinistra libera
        pthread_mutex_lock(&mutex);
        if(forcs[id] == -1){
            forcs[id] = id;
            //printf("[%d] Ho preso la forchetta libera a sinistra -%d-\n", id, forcs[id]);
        }
        pthread_mutex_unlock(&mutex);
        
        //se ho preso una forchetta a sinistra e una a destra è libera, posso prenderla
        pthread_mutex_lock(&mutex);
        if(forcs[id]==id && forcs[(id+1)%5]==-1){
            forcs[(id+1)%5] = id;
            dueF = 1;
            //printf("[%d] Ho preso la forchetta libera a destra -%d-\n", id, forcs[(id+1)%5]);
        }
        pthread_mutex_unlock(&mutex);

        //Due forchette, il filosofo può mangiare
        if(dueF){
            printf(BLUE "[%d] Sto mangiando...\n" RESET, id);
            usleep(10000*(rand()%100));

            pthread_mutex_lock(&mutex);
            forcs[id] = -1;
            forcs[(id+1)%5] = -1;
            dueF = 0;
            pthread_mutex_unlock(&mutex);
        }
        
        //una o nessuna forchetta, il filosofo pensa
        else{
            printf(RED "[%d] Sto pensando...\n" RESET, id);
            usleep(10000*(rand()%100));
        }
    }
    usleep(10000*(rand()%100));    
    return NULL;
}

// Funzione di gestione del segnale
void handle_sigint(int sig) {
    printf("\n" RESET, sig);
    exit(0); // Esci dal programma
}

int main(){

    // Registra la funzione di gestione del segnale
    signal(SIGINT, handle_sigint);

    printf(MAGENTA "Programma che implementa il problema dei filosofi a cena tramite i threads\n\n" RESET);

    srand(time(NULL));

    /*dentro ogni cella di forcs[] c'è l'id del filosofo che l'ha presa, altrimenti -1
    (libera = -1, presa = id)*/

    //nessuno ha preso le forchette
    for(int i=0; i<NUM; i++){
        forcs[i] = -1;
    } 

    //creazione threads
    for(int i=0; i<NUM; i++){
        /*con create() accedo al valore della cella di memoria di ogni thread e gli
        assegno un TID*/
        if(pthread_create(fil+i, NULL, routine, NULL) != 0){
            fprintf(stderr, "Errore creazione threads\n");
            exit(1);
        }
    }

    //attesa threads
    for(int i=0; i<5; i++){
        /*con join() accedo alla cella di memoria (ora contenente il TID) di ogni thread
        e attendo che termini*/
        pthread_join(*(fil+i), NULL);
    }
    return 0;
}