#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define DIM 100

int main(){

    printf("Programma che stampa un messaggio su un file e lo carica dallo stesso\n\n");

    //creazione file
    int fd = open("Messaggio.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
   
    //creazione file fallita
    if(fd == -1){
        fprintf(stderr, "Errore nella creazione del file\n");
        close(fd);
        exit(1);
    }

    //buffer per la scrittura
    char bufferW[DIM];

    printf("Digita il tuo messaggio da scrivere sul file: ");
    scanf("%s", bufferW);

    //scrittura su file, altrimenti errore
    /*file descriptor, spazio memoria da dove prendere messaggio, lunghezza messaggio che si vuole prendere*/ 
    if(write(fd, bufferW, strlen(bufferW)) == -1){ 
        fprintf(stderr, "Errore nella scrittura sul file\n");
        close(fd);
        exit(1);
    }

    close(fd);

    //file in modalità lettura
    fd = open("Messaggio.txt", O_RDONLY);

    //creazione file fallita
    if(fd == -1){
        fprintf(stderr, "Errore nell'apertura del file per la lettura\n");
        close(fd);
        exit(1);
    }

    //buffer per la lettura
    char bufferR[DIM];

    //lettura file
    fd = read(fd, bufferR, strlen(bufferW));
    printf("Messaggio scritto sul file: %s\n\n", bufferR);

    //lettura file fallita
    if(fd == -1){
        fprintf(stderr, "Errore nella lettura\n");
        close(fd);
        exit(1);
    }
    return 0; 
}