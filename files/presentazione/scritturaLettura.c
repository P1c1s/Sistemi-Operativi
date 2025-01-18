#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

#define DIM 10

int main(){

    printf("Programma che scrive dei numeri in un file e poi li legge dal file.\n\n");

    int fd = open("Pippo.txt", O_CREAT | O_WRONLY, S_IRWXU);
    if (fd == -1)
        printf("Document non creato\n");

    srand(time(NULL));

    for(int i=0; i<DIM; i++){
        int numero = rand()%90+10;
        char* stringa = (char*) malloc(4*sizeof(char));
        sprintf(stringa, "%d\n", numero);
        int scrittura = write(fd, stringa, strlen(stringa));
        printf("Numero di byte scritti: %d\n", scrittura);
    }
    //free(string);
    close(fd);

    int* vettore = (int*) malloc(DIM*sizeof(int));

    fd = open("Pippo.txt", O_RDONLY, S_IRWXU);
     
    // --- soluzione chat gpt
    char lettura[3];
    int i = 0;
    while (read(fd, lettura, sizeof(lettura)) > 0 && i < DIM) {
        vettore[i] = atoi(lettura);
        i++;
    }
    //-------------

    for(int i=0; i<DIM; i++)
        printf("[Posizione %d] : %d\n", i, *(vettore+i));

    return 0;
}