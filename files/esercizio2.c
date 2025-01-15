#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>


#define DIM 10

typedef struct Persona {
    char nome[30];
    char cognome[30];
    char numero[10];
}Persona;

typedef struct Rubrica {
    Persona contatti[DIM];
    int indice;
}Rubrica;

void aggiungiPersona(Rubrica *r){
    printf("Inserisci nome: ");
    scanf("%s", &r->contatti[r->indice].nome);
    printf("Inserisci cognome: ");
    scanf("%s", &r->contatti[r->indice].cognome);
    printf("Numero: ");
    scanf("%s", &r->contatti[r->indice].numero);
    r->indice += 1;
}

void stampa(Rubrica r){
    printf("\n\n\nRubrica telefonica\n\n");
    for(int i=0; i<r.indice; i++){
        printf("Nome: %s\n", r.contatti[i].nome);
        printf("Cognome %s\n", r.contatti[i].cognome);
        printf("Numero: %s\n\n", r.contatti[i].numero);
    }
}

void salvataggio(Rubrica r){
    int fd = open("rubrica.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    for(int i=0; i<r.indice; i++){
        if(write(fd, r.contatti[i].nome, 30*sizeof(char)) == -1){
            fprintf(stderr, "Errore scrittura nome");
            exit(1);
        }
        if(write(fd, r.contatti[i].cognome, 30*sizeof(char)) == -1){
            fprintf(stderr, "Errore scrittura nome");
            exit(1);
        }
        if(write(fd, r.contatti[i].numero, 10*sizeof(char)) == -1){
            fprintf(stderr, "Errore scrittura nome");
            exit(1);
        }
    }
    close(fd);
}

void caricamento(Rubrica* r){
    int fd = open("rubrica.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    char a[30];

    // while(read(fd, a, sizeof(buffer) - 1) > 0){
    //     buffer[bytes_read] = '\0'; // Aggiungi un terminatore di stringa
    //     printf("%s", buffer); // Stampa i dati letti
    // }

    read(fd, &r->contatti[0].nome, 30*sizeof(char));
    read(fd, &r->contatti[0].cognome, 30*sizeof(char));
    read(fd, &r->contatti[0].numero, 10*sizeof(char));
    r->indice =+ 1;
    close(fd);

}

int main(){

    Rubrica rubrica;
    rubrica.indice = 0;
    int comando;

    do{
        printf("\n\n-------------Menu'-----------\n");   
        printf("1) Inserimento nuovo contatto\n");
        printf("2) Stampa\n");
        printf("3) Salvataggio su file\n");
        printf("4) Caricamento da file\n");
        printf("0) Esci\n");
        printf("comando atteso: ");
        scanf("%d", &comando);
        if(comando == 1)
            aggiungiPersona(&rubrica);
        else if(comando == 2)
            stampa(rubrica);
        else if(comando == 3)
            salvataggio(rubrica);
        else if(comando == 4)
            caricamento(&rubrica);
    }while(comando != 0);


    // if(fd == -1){
    //     fprintf(stderr, "Errore apertura files\n");
    //     exit(1);
    // }

    // for(int i=0; i<DIM; i++)
    //     printf("%d", vettore[i]);

    // for(int i=0; i<DIM; i++){
    //     itoa(vettore[i], carattere, 10);
    //     scrittura = write(fd, carattere, sizeof(int));
    // }
    
    // if (close(fd) == -1) {
    //     perror("Error closing file");
    //     return 1;
    // }

    return 0;

}