#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

#define DIM 100

int main(){

    //creazione file per scrittura
    int fd = open("Messaggio.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    if(fd == -1){
        fprintf(stderr, "Errore creazione file per scrittura\n");
        close(fd);
        exit(1);
    }

    char mex[100];

    printf("Digita il messaggio da scrivere nel file: ");
    scanf("%s", mex);

    //scrittura file
    for(int i=0; i<strlen(mex); i++){
        if(write(fd, &mex[i], sizeof(char)) == -1){
            fprintf(stderr, "Errore scrittura file\n");
            close(fd);
            exit(1);
        }
    }
    close(fd);

    fd = open("Messaggio.txt", O_RDONLY);

    if(fd == -1){
        fprintf(stderr, "Errore creazione file per lettura\n");
        close(fd);
        exit(1);
    }

    for(int i=0; i<strlen(mex); i++){
       if(read(fd, &mex[i], sizeof(char)) == -1){
           fprintf(stderr, "Errore lettura file\n");
            close(fd);
            exit(1); 
       } 
    }

    printf("Messaggio scritto sul file: ");
    for (int i=0; i<strlen(mex); i++){
        printf("%c", mex[i]);
    }
    printf("\n\n");
    close(fd);
    return 0;
}