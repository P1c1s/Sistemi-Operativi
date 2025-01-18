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
    if(fd == -1){
        fprintf(stderr, "Errore apertura file per la scrittura");
        exit(1);
    }
    for(int i=0; i<r.indice; i++){
        if(write(fd, r.contatti[i].nome, 30*sizeof(char)) == -1){
            fprintf(stderr, "Errore scrittura persona %d", i);
            close(fd);
            exit(1);
        }
	if(write(fd, r.contatti[i].cognome, 30*sizeof(char)) == -1){
            fprintf(stderr, "Errore scrittura cognome");
            close(fd);
            exit(1);
        }
	if(write(fd, r.contatti[i].numero, 10*sizeof(char)) == -1){
            fprintf(stderr, "Errore scrittura numero");
            close(fd);
            exit(1);
        }
    }
    close(fd);
}

void caricamento(Rubrica *r) {
    int fd = open("rubrica.txt", O_RDONLY);
    if (fd == -1) {
        perror("Errore nell'apertura del file per lettura");
        exit(1);
    }
    r->indice = 0; // Resetta l'indice
    while(read(fd, &r->contatti[r->indice], sizeof(Persona)) > 0) {
        r->indice++;
        if (r->indice >= DIM) {
            printf("Rubrica piena, non possono essere caricati ulteriori contatti.\n");
            break;
        }
    }

    printf("\nCaricati %d contatti.\n", r->indice);
    
    close(fd);
}

int main(){

    Rubrica rubrica;
    rubrica.indice = 0;
    int comando;
    
    printf("Programma che gestisce una rubrica telefonica salvandola e ricaricadola da un file.\n\n");

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

    return 0;

}