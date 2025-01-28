#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

#define n 4

#define RESET   "\033[0m"  // Reset del colore
#define RED     "\033[31m" // Rosso
#define GREEN   "\033[32m" // Verde
#define YELLOW  "\033[33m" // Giallo
#define BLUE    "\033[34m" // Blu
#define MAGENTA "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano
#define WHITE   "\033[37m" // Bianco

void* dormire(void*);
void* produrre(void*);
void* clientare(void*);

pthread_mutex_t sedie[n]; //le sedie sono risorse "condivise" --> se un cliente ne prende una però non può essere presa dagli altri
pthread_mutex_t sediaBarbiere = PTHREAD_MUTEX_INITIALIZER;       //anche la sedia del barbiere è una risorsa "condivisa". 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int clienti = 0;
int indice = 0;

pthread_t barbiere;
pthread_t produttoreClienti;
pthread_t cliente;

int main(){
    srand(time(NULL));

    for(int i=0; i<n; i++){
        pthread_mutex_init(sedie+i, NULL);
    }

    pthread_create(&barbiere, NULL, dormire, NULL);
    pthread_create(&produttoreClienti, NULL, produrre, NULL);

    while(1){
        printf(MAGENTA "\nNumero clienti: %d\n", clienti);
        sleep(2);
    }

    pthread_join(barbiere, NULL);
    pthread_join(produttoreClienti, NULL);

    for(int i=0; i<n; i++){
        pthread_mutex_destroy(sedie+i);
    }
    pthread_mutex_destroy(&sediaBarbiere);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void* dormire(void* arg){
    while(1){
        if (clienti == 0 ){
            pthread_mutex_lock(&sediaBarbiere);
            printf(WHITE "Il barbiere sta dormendo\n");
            usleep(rand()%100 * 1000);      //tempo in cui il barbiere dorme
            //pthread_mutex_unlock(&sediaBarbiere);
        }
        else{
            pthread_mutex_unlock(&sediaBarbiere);
        }
    }
    return NULL;
}

void* produrre(void* arg){
    while(1){
        pthread_create(&cliente, NULL, clientare, NULL);
        //pthread_join(cliente, NULL);
        //usleep(rand()%100 * 1000);
        usleep(((rand()%100)+50) * 10000);
    }
    return NULL;
}

void* clientare(void* arg){
    if (clienti == (n+1)){              //tutte le sedie sono occupate e il cliente va via
        printf(RED "[TID : %lu] \tCliente scartato\n", (unsigned long) pthread_self());
    }
    else if (clienti == 0){
        pthread_mutex_lock(&mutex);
        clienti++;                      //incremento contatore clienti presenti nel negozio
        printf(WHITE "[TID : %lu] \tCliente arrivato \n", (unsigned long) pthread_self());
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&sediaBarbiere);      //essendo il cliente 1 si siede direttamente nella sedia del taglio

        printf(CYAN "[TID : %lu] \tSta tagliando i capelli \n", (unsigned long) pthread_self());
        printf(BLUE "[TID : %lu] \tLock preso dal primo cliente\n");
        usleep(rand()%100 * 10000);                       //tempo taglio di capelli
        printf(CYAN "[TID : %lu] \tHa finito \n", (unsigned long) pthread_self());

        pthread_mutex_unlock(&sediaBarbiere);

        pthread_mutex_lock(&mutex);
        clienti--;                      //decremento contatore clienti presenti nel negozio
        printf(GREEN "[TID : %lu] \tCliente andato via \n", (unsigned long) pthread_self());
        pthread_mutex_unlock(&mutex);

    }
    else if (clienti >= 1 && clienti < (n+1)){
        pthread_mutex_lock(&mutex);             //mutex per incremento clienti e indice
        clienti++;
        printf(WHITE "[TID : %lu] \tCliente arrivato \n", (unsigned long) pthread_self());
        int index = indice%4;
        
        pthread_mutex_lock(&sedie[index]);      //incrementa numero di clienti ma si deve sedere nelle sedie d'attesa
        indice++;
        printf(YELLOW "[TID : %lu] \tAttende nella sedia %d, indice. %d\n", (unsigned long) pthread_self(), index+1, index);
        pthread_mutex_unlock(&mutex);           //rilascio clienti e indice
        pthread_mutex_lock(&sediaBarbiere);     //attendo e prendo lock sedia taglio
        printf(BLUE "[TID : %lu] \tLock preso da chi sedeva nella sedia %d, indice. %d\n", (unsigned long) pthread_self(), index+1, index);
        pthread_mutex_unlock(&sedie[index]);         //se sono sulla poltrona dle taglio rilascio la poltrona d'attesa
        
        printf(CYAN "[TID : %lu] \tSta tagliando i capelli \n", (unsigned long) pthread_self());
        sleep(rand()%10);       //taglio capelli
        printf(CYAN "[TID : %lu] \tHa finito \n", (unsigned long) pthread_self());

        pthread_mutex_unlock(&sediaBarbiere);

        pthread_mutex_lock(&mutex);
        clienti--;                      //decremento contatore clienti presenti nel negozio
        printf(GREEN "[TID : %lu] \tCliente andato via \n", (unsigned long) pthread_self());
        pthread_mutex_unlock(&mutex);        
    } 
    return NULL;
}