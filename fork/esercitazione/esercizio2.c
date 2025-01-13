#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){

    printf("Programma che prima scrive in file.txt\n");
    printf("1) genitore scrive il titolo nel file\n");
    printf("2) genitore scrive nel file\n");
    printf("3) figlio scrive nel file\n\n");
    printf("NB: L'ordine dei punti 2 e 3 viene deciso dallo scheduler\n");


    int  fd = open("file.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    if (fd == -1) {
        fprintf(stderr, "Errore\n");
        exit(1);
    }else{
        char titolo[] = "File descriptor ";
        char fdCarattere[10];
        sprintf(fdCarattere, "%d", fd); //to string
        int scrittura = write(fd, titolo, sizeof(titolo));
        scrittura = write(fd, fdCarattere, sizeof(fdCarattere));
        scrittura = write(fd, "\n\n", sizeof("\n\n"));
    }

    int pid = fork();

    if(pid>0){
        char messaggio[] = "[genitore] Sto scrivendo nel file.\n";
        int scrittura = write(fd, messaggio, sizeof(messaggio));
        if(scrittura<0){
            fprintf(stderr, "Errore scrittura padre\n");
            exit(1);
        }
    } else if(pid==0){
        char messaggio[] = "[figlio] Sto scrivendo nel file.\n";
        int scrittura = write(fd, messaggio, sizeof(messaggio));
        if(scrittura<0){
            fprintf(stderr, "Errore scrittura figlio\n");
            exit(1);
        }
    } else if(pid<0){
        fprintf(stderr, "Errore\n");
        exit(1);
    }

    return 0;

}
