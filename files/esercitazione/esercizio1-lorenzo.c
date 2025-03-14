#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define FILE "originale.txt"

int controlloGrandezza(){
    char *carattere = (char*)malloc(sizeof(char));
    int i = 0;
    int fd = open(FILE, O_CREAT | O_RDONLY, S_IRWXU);
    if(fd == -1){
        fprintf(stderr, "Errore aperura file - controlloGrandezza()\n");
        close(fd);
        exit(1);
    }
    while(read(fd, carattere, sizeof(char)) > 0)
        i++;
    close(fd);
    
    if(i >= 1000)
        printf("%s non copiato, grandezza file non supportata\n", FILE);

    return i;
}

void copia(){
    char* carattere = (char*)malloc(sizeof(char));
    int fdOriginale = open(FILE, O_CREAT | O_RDWR, S_IRWXU);
    int fdCopia = open("copia.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    if(fdOriginale == -1){
        fprintf(stderr, "Errore apertura fileOriginale - copia()\n");
        close(fdOriginale);
    }

    if(fdCopia == -1){
        fprintf(stderr, "Errore apertura fileCopia - copia()\n");
        close(fdCopia);
    }

    while(read(fdOriginale, carattere, sizeof(char)) > 0){
        write(fdCopia, carattere, sizeof(char));
    }

    close(fdOriginale);
    close(fdCopia);
    printf("%s copiato correttamente in copia.txt\n", FILE);
}

void generazione(){
    int bytes = 10 * (rand()%500);
    int fd = open(FILE, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    if(fd == -1){
        fprintf(stderr, "Errore apertura file - generazione()\n");
        close(fd);
    }

    for(int i=0; i<bytes; i++){
        char carattere = 97 + rand()%24;
        write(fd, &carattere, sizeof(char));
    }
    close(fd);
    printf("Generato file da %d bytes\n", bytes);
}

int main(){

    printf("Programma che crea una copia di un file generato randomicamente qualora la dimensine del file sia inferiore a 1000 bytes\n\n");

    srand(time(NULL));

    generazione();

    if(controlloGrandezza() <= 1000)
        copia();

    return 0;
}