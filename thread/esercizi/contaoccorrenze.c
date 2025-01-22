#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>

// !NOTA : Prima di eseguirlo assicurarsi di aver creato un file di testo "Testo.txt"

void* occorrenze(void*);

char titolo[] = "Testo.txt";

int main(){

    pthread_t t[5];
    char* lettera = (char*) malloc(5*sizeof(char));
    printf("Inserire 5 lettere di cui contare le occorrenze\n\n");
    for(int i=0; i<5; i++){
        printf("Inserisci %da lettera: ", i+1);
        scanf("%c%*c", &lettera[i]);
        //pthread_create(t+i, NULL, occorrenze, (void*) lettera+i);
    }

    for(int i=0; i<5; i++){
        pthread_create(t+i, NULL, occorrenze, (void*) lettera+i);
    }

    for(int i=0; i<5; i++){
        pthread_join(*(t+i), NULL);
    }
    
    return 0;
}

void* occorrenze(void* lettera){
    char daCercare = *((char*) lettera);

    int counter = 0;
    int fd = open(titolo, O_RDONLY, S_IRWXU);
    if(fd == -1)
        fprintf(stderr, "Errore nell'apertura del file");

    char* letto = (char*) malloc(sizeof(char));
    while(read(fd, letto, sizeof(char)) > 0){
        if (*letto == daCercare)
            counter++;
    }

    printf("[%c] Occorrenze: %d\n", daCercare, counter);
    return NULL;
}