#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>

#define DIM 100
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

typedef struct Pila{
    int buffer[DIM];
    int indice;
}Pila;

typedef struct Somme{
    int addendoUno;
    int addendoDue;
    int risultato;
}Somme;

typedef struct S{
    Somme somme[DIM];
    int indice;
}S;

Pila pila;
S s;

void stampaProduttore(){
    printf("[ Prod ]  ");
    printf("{");
    for(int i=0; i<pila.indice; i++)
        printf(" %d", pila.buffer[i]);
    printf(" }\n");
}

void stampaConsumatore(){
    printf("[ Cons ]  ");
    printf("%d +", s.somme[s.indice-1].addendoUno );
    printf(" %d =", s.somme[s.indice-1].addendoDue );
    printf(" %d\n", s.somme[s.indice-1].risultato);
}

void* produttore(void* arg){

    while(1){
        pthread_mutex_lock(&mutex1);
        pila.buffer[pila.indice] = rand()%30+10;
        pila.indice++;
        stampaProduttore();
        pthread_mutex_unlock(&mutex1);
        usleep(1000*10*(rand()%100));
    }

    return NULL;
}

void* calcolatore(void* arg){

    while(1){
        pthread_mutex_lock(&mutex2);
        pthread_mutex_lock(&mutex1);
        pila.indice--;
        s.somme[s.indice].addendoUno = pila.buffer[pila.indice];
        pila.indice--;
        s.somme[s.indice].addendoDue = pila.buffer[pila.indice];
        pthread_mutex_unlock(&mutex1);
        s.somme[s.indice].risultato =  s.somme[s.indice].addendoUno  + s.somme[s.indice].addendoDue;
        s.indice++; 
        stampaConsumatore();
        pthread_mutex_unlock(&mutex2);
        usleep(1000*50*(rand()%100));
    }

    return NULL;
}

void* scrittore(void* arg){

    while(1){
        char* carattere = (char*)malloc(sizeof(char));
        int fd = open("FILE.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
        if(fd == -1){
            fprintf(stderr, "Errore aperura file\n");
            close(fd);
            exit(1);
        }

        pthread_mutex_lock(&mutex2);
        pthread_mutex_lock(&mutex1);

        for(int i=0; i<s.indice; i++){
            int unita = s.somme[i].addendoUno%10;
            int decine = (s.somme[i].addendoUno-unita)/10;
            sprintf(carattere, "%d", decine);
            write(fd, carattere, sizeof(char));
            sprintf(carattere, "%d", unita);
            write(fd, carattere, sizeof(char));

            write(fd, "+", sizeof(char));

            unita = s.somme[i].addendoDue%10;
            decine = (s.somme[i].addendoDue-unita)/10;
            sprintf(carattere, "%d", decine);
            write(fd, carattere, sizeof(char));
            sprintf(carattere, "%d", unita);
            write(fd, carattere, sizeof(char));

            write(fd, "=", sizeof(char));

            unita = s.somme[i].risultato%10;
            decine = (s.somme[i].risultato-unita)/10;
            sprintf(carattere, "%d", decine);
            write(fd, carattere, sizeof(char));
            sprintf(carattere, "%d", unita);
            write(fd, carattere, sizeof(char));

            write(fd, "\n", sizeof(char));
        }
        close(fd);
        printf("[ Scri ] Salvataggio effettuato\n");
        pthread_mutex_unlock(&mutex1);
        pthread_mutex_unlock(&mutex2);
        sleep(5);
    }
    return NULL;
}

int main(){

    printf("\n\n");
    srand(time(NULL));
    pila.indice = 0;
    s.indice = 0;
    pthread_t prod, calc, scri;
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);

    pthread_create(&prod, NULL, produttore, NULL);
    pthread_create(&calc, NULL, calcolatore, NULL);
    pthread_create(&scri, NULL, scrittore, NULL);

    pthread_join(prod, NULL);
    pthread_join(calc, NULL);
    pthread_join(scri, NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;
}