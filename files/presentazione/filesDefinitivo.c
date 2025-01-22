#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define DIM 100

void scriviLeggiNotoPerIntero(){
    /*SCRITTURA*/
    int fd = open("Definitivo.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    if(fd == -1){
        fprintf(stderr, "Errore apertura file per scrittura\n");
        close(fd);
        exit(1);
    }

    char mex[] = "Ciao";

    if(write(fd, mex, strlen(mex)) == -1){
        fprintf(stderr, "Errore scrittura file");
        close(fd);
        exit(1);
    }

    printf("Ho scritto per intero il messaggio noto -%s- dal file.\n", mex);
    close(fd);

    /*LETTURA*/
    fd = open("Definitivo.txt", O_RDONLY, S_IRWXU);

    if(fd == -1){
        fprintf(stderr, "Errore apertura file per lettura\n");
        close(fd);
        exit(1);
    }

    if(read(fd, mex, strlen(mex)) == -1){
        fprintf(stderr, "Errore lettura file");
        close(fd);
        exit(1);
    }
    printf("Ho letto per intero il messaggio noto -%s- dal file.", mex);
    close(fd);
}

void scriviLeggiNotoPerCarattere(){
    /*SCRITTURA*/
    int fd = open("Definitivo.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    if(fd == -1){
        fprintf(stderr, "Errore apertura file per scrittura");
        close(fd);
        exit(1);
    }

    char mex[] = "Ciao";

    for (int i=0; i<strlen(mex); i++){
        if(write(fd, &mex[i], sizeof(char)) == -1){
            fprintf(stderr, "Errore scrittura file");
            close(fd);
            exit(1);
        }
    }
    printf("Ho scritto carattere per carattere il messaggio noto -%s- dal file.\n", mex);
    close(fd);

    /*LETTURA*/
    fd = open("Definitivo.txt", O_RDONLY, S_IRWXU);
    
    if(fd == -1){
        fprintf(stderr, "Errore apertura file per lettura\n");
        close(fd);
        exit(1);
    }
    
    for(int i=0; i<strlen(mex); i++){
        if(read(fd, &mex[i], sizeof(char)) == -1){
            fprintf(stderr, "Errore lettura file");
            close(fd);
            exit(1);
        }
    }
    printf("Ho letto carattere per carattere il messaggio noto -%s- dal file.", mex);
    close(fd);
}

void scriviLeggiMexPerIntero(){
    char mex[DIM];

    printf("Digita il messaggio di seguito: ");
    scanf("%s", &mex);

    /*SCRITTURA*/
    int fd = open("Definitivo.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    
    if(fd == -1){
        fprintf(stderr, "Errore apertura file per scrittura");
        close(fd);
        exit(1);
    }
    
    if(write(fd, mex, strlen(mex)) == -1){
        fprintf(stderr, "Errore scrittura file");
        close(fd);
        exit(1);
    }
    printf("Ho scritto per intero il messaggio -%s- scritto dall'utente sul file.\n", mex);
    close(fd);

    /*LETTURA*/
    fd = open("Definitivo.txt", O_RDONLY, S_IRWXU);

    if(read(fd, mex, strlen(mex)) == -1){
        fprintf(stderr, "Errore lettura file");
        close(fd);
        exit(1);
    }
    printf("Ho letto per intero il messaggio -%s- scritto dall'utente sul file.", mex);
    close(fd);
}

void scriviLeggiMexPerCarattere(){
    char mex[DIM];

    printf("Digita il messaggio di seguito: ");
    scanf("%s", &mex);

    /*SCRITTURA*/
    int fd = open("Definitivo.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    
    if(fd == -1){
        fprintf(stderr, "Errore apertura file per scrittura");
        close(fd);
        exit(1);
    }
    
    for (int i=0; i<strlen(mex); i++){
        if(write(fd, &mex[i], sizeof(char)) == -1){
            fprintf(stderr, "Errore scrittura file");
            close(fd);
            exit(1);
        }
    }
    printf("Ho scritto carattere per carattere il messaggio -%s- scritto dall'utente sul file.\n", mex);
    close(fd);

    /*LETTURA*/
    fd = open("Definitivo.txt", O_RDONLY, S_IRWXU);

    for (int i=0; i<strlen(mex); i++){
        if(read(fd, &mex[i], sizeof(char)) == -1){
            fprintf(stderr, "Errore lettura file");
            close(fd);
            exit(1);
        }
    }
    printf("Ho letto carattere per carattere il messaggio -%s- scritto dall'utente sul file.", mex);
    close(fd);
}

int main(){

    printf("Programma che scrive e legge da un file in modi diversi\n\n");

    int comando;

    do{
        printf("\n\nCOMANDI:\n\n");
        printf("1) SCRIVI E LEGGI \"Ciao\" PER INTERO DA UN FILE\n");
        printf("2) SCRIVI E LEGGI \"Ciao\" CARATTERE PER CARATTERE DA UN FILE\n");
        printf("3) DIGITA E LEGGI UN MESSAGGIO PER INTERO DA UN FILE\n");
        printf("4) DIGITA E LEGGI UN MESSAGGIO CARATTERE PER CARATTERE DA UN FILE\n");
        printf("0) ESCI\n");

        printf("Comando: ");
        scanf("%d", &comando);
        printf("\n\n");

        if(comando == 1)
            scriviLeggiNotoPerIntero();
        if(comando == 2)
            scriviLeggiNotoPerCarattere();
        if(comando == 3)
            scriviLeggiMexPerIntero();
        if(comando == 4)
            scriviLeggiMexPerCarattere();
    }
    while(comando != 0);

    return 0;
}