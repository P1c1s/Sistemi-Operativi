#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<time.h>

//funzione che crea il file e scrive un numero di caratteri random al suo interno
void generazione(){

    int fd = open("File.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);

    if(fd == -1){
        fprintf(stderr, "Errore apertura file in scrittura\n");
        close(fd);
        exit(1);
    }

    int num = rand()%1500;

    char* carattere = (char*)malloc(sizeof(char));
    *carattere = 'f';

    for(int i=0; i<num; i++)
        write(fd, carattere, sizeof(char));
    
    close(fd);
}

int controllo(){

    int fd = open("File.txt", O_CREAT | O_RDONLY, S_IRWXU);

    if(fd == -1){
        fprintf(stderr, "Errore apertura file in lettura\n");
        close(fd);
        exit(1);
    }

    char* carattere = (char*)malloc(sizeof(char));

    int letto = 0;

    while(read(fd, carattere, sizeof(char)) > 0)
        letto++;

    close(fd);

    printf("Numero caratteri nel file: [%d]\n", letto);

    return letto;
}

void copia(){

    int fd = open("File.txt", O_CREAT | O_RDONLY, S_IRWXU);

    int fd1 = open("Copia.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    char* carattere = (char*)malloc(sizeof(char));

    while(read(fd, carattere, sizeof(char)) > 0)
        write(fd1, carattere, sizeof(char));

    close(fd);
    close(fd1);

    printf("Copia effettuata!\n");
}

int main(){
    
    printf("Programma che crea un file di lunghezza random; se il file generato non ");
    printf("supera i 1000 bytes viene copiato in un altro, altrimenti no\n\n");

    srand(time(NULL));

    generazione();

    if(controllo() < 1000)
        copia();
    else
        printf("Copia non disponibile\n");

    return 0;
}