#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>

#define titolo "Pippo3.txt"
#define max 1000

void creazione();
void copia();

int main(){

    srand(time(NULL));
    creazione();

    copia();

    return 0;
}


void creazione(){
    int fd = open(titolo, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
    if (fd == -1){
        fprintf(stderr, "Errore nell'apertura del file\n");
        exit(1);
    }

    for(int i=0; i<((rand()%300)+900); i++){
        char* carattere = (char*) malloc(sizeof(char));
        *carattere = (char) ((rand()%74) + 48);
        int b = write(fd, carattere, sizeof(char));
        if (b < 0){
            fprintf(stderr, "Errore nella scrittura di un carattere\n");
            exit(1);
        }
    }

    close(fd);
}

void copia(){

    int fd = open(titolo, O_RDONLY, S_IRWXU);

    char* testo = (char*) malloc(1400*sizeof(char));
    int b = read(fd, testo, 1400*sizeof(char));

    if(b < 0){
        fprintf(stderr, "Errore nella lettura del file\n");
        exit(1);
    }
    else if (b > 1000){
        printf("Dimensione: [%d bytes]\n", b);
        printf("File troppo grande, copia non permessa\n");
    }
    else if (b > 0 && b < 1000){
        printf("Dimensione: [%d bytes]\n", b);
        int fdcopia = open("Copia.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
        if (fdcopia < 0){
            fprintf(stderr, "Errore nella creazione del file copia\n");
            exit(1);
        }

        int bcopia = write(fdcopia, testo, sizeof(char));
        if (bcopia < 0){
            fprintf(stderr, "Errore nella copia del file\n");
        }
        else
            printf("File copiato con successo\n");

        close(fdcopia);
    }
    close(fd);
}


//65-122