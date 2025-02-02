#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<pthread.h>
#include<string.h>

typedef struct dati{
    int* vettore;
    int numElementi;
}Dati;

Dati* addendi;
Dati* operazioni;

void* produttore(void*);
void* sommatore(void*);
void* scrittore(void*);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


int main(){
    srand(time(NULL));

    addendi = (Dati*) malloc(sizeof(Dati));
    operazioni = (Dati*) malloc (sizeof(Dati));
    addendi->vettore = NULL;
    operazioni->vettore = NULL;
    addendi->numElementi = 0;
    operazioni->numElementi = 0;

    pthread_t prod, somma, scritt;

    pthread_create(&prod, NULL, produttore, NULL);
    pthread_create(&somma, NULL, sommatore, NULL);
    pthread_create(&scritt, NULL, scrittore, NULL);

    pthread_join(prod, NULL);
    pthread_join(somma, NULL);
    pthread_join(scritt, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}

void* produttore(void* args){

    while(1){

        int index = addendi->numElementi;
        int* vett = addendi->vettore;

        pthread_mutex_lock(&mutex);

        if (index == 0)
            addendi->vettore = (int*) malloc(2*sizeof(int));
        else
            addendi->vettore = (int*) realloc(vett, (index + 2) * sizeof(int));

        *(vett+index) = rand()%100;
        addendi->numElementi++;
        index++;
        *(vett+index) = rand()%100;
        addendi->numElementi++;

        pthread_mutex_unlock(&mutex);


        usleep((rand()%100)*1000);
    }

    return NULL;
}

void* sommatore(void* args){
    while(1){

        int index = operazioni->numElementi;
        int* vettOp = operazioni->vettore;

        int ind = addendi->numElementi;
        int* vettAdd = addendi ->vettore;

        pthread_mutex_lock(&mutex);


        if(ind == 0)
            printf("Non ci sono elementi da sommare\n");
        else{
            if(index == 0)
                operazioni->vettore = (int*) malloc(3*sizeof(int));
            else
                operazioni->vettore = (int*) realloc(vettOp, (index + 3) * sizeof(int));

            *(vettOp + index) = *(vettAdd + (ind - 2));
            operazioni->numElementi++;
            index++;
            *(vettOp + index) = *(vettAdd + (ind - 1));
            operazioni->numElementi++;
            index++;

            *(vettOp + index) = *(vettAdd + (ind - 2)) + *(vettAdd + (ind - 1));
            operazioni->numElementi++;

            if(ind == 2){
                free(addendi->vettore);
            }
            else{
                addendi->vettore = (int*) realloc(addendi->vettore, (ind-2) * sizeof(int));
                addendi->numElementi = addendi->numElementi-2;
            }

        }

        pthread_mutex_unlock(&mutex);

        usleep((rand()%100)*1000);

    }

    return NULL;
}

void* scrittore(void* args){

    while(1){

        pthread_mutex_lock(&mutex);

        if(operazioni->numElementi == 0)
            printf("Non ci sono somme da scrivere\n");

        else{
            int fd = open("Somme.txt", O_CREAT | O_WRONLY, S_IRWXU);
            if(fd < 0){
                fprintf(stderr, "Errore nell'apertura del file");
                exit(1);
            }

            int index = operazioni->numElementi;
            int* vett = operazioni->vettore;

            char* stringa = (char*) malloc(15*sizeof(char));

            sprintf(stringa, "%d + %d = %d\n", *(vett+(index -3)), *(vett+(index - 2)), *(vett+(index - 1)));
            int b = write(fd, stringa, strlen(stringa));

            if (b < 0){
                fprintf(stderr, "Errore nella scrittura sul file");
                exit(1);
            }
            else{
                operazioni->vettore = (int*) realloc(operazioni->vettore, (index-3) * sizeof(int));
                operazioni->numElementi = operazioni->numElementi-3;
            }

            close(fd);
        }
        pthread_mutex_unlock(&mutex);

        sleep(5);
    }

}