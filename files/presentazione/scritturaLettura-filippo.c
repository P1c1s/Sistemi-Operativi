#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<string.h>

#define DIM 10

int main(){

    printf("\n\nProgramma che stampa dei numeri su un file e poi li legge dallo stesso file\n\n");

    //creazione file
    int fd = open("Pippo.txt", O_CREAT | O_WRONLY, S_IRWXU);
    
    //creazione file fallita
    if(fd == -1){
        fprintf(stderr, "Errore nella creazione del file\n");
        exit(1);
    }

    //scrittura sul file di numeri random
    for (int i=0; i<DIM; i++){
        //numero random tra 1 e 89 di due cifre
        int numero = rand()%90+10;
        
        //stringa che conterrà il numero da scrivere sul file
        char* stringa = (char*)malloc(4*sizeof(char));
        //funzione che "trasforma" un intero in un carattere -> lo '\n' indica che la stringa continua
        sprintf(stringa, "%d\n", numero);

        //scrittura sul file
        int scrittura = write(fd, stringa, strlen(stringa));

        //Scrittura su file fallita
        if(scrittura == -1){
            fprintf(stderr, "Errore nella scrittura sul file\n");
            exit(1);
        }
        else
            //stampa dei byte scritti (valore restituito dalla write)
            printf("Byte scritti: %d\n", scrittura);
    }

    //chiudo il file
    close(fd);

    //vettore per stampare gli interi letti dal file
    int* vettore = (int*)malloc(DIM*sizeof(int));

    //apro il file in modalità lettura
    fd = open("Pippo.txt", O_RDONLY, S_IRWXU);

    //spazio di buffer dove inserire i 3 caratteri letti
    char lettura[3];

    //contatore
    int i = 0;

    //legge tutti i caratteri dal file e li inserisce nel vettore creato prima
    while(read(fd, lettura, sizeof(lettura))>0 && i<DIM){
        vettore[i] = atoi(lettura);
        i++;
    }
    
    //lettura file fallita
    if(read(fd, lettura, sizeof(lettura)) == -1){
        fprintf(stderr, "Errore nella lettura del file\n");
        exit(1);
    }
    
    //stampa tutti gli interi letti dal file
    printf("Vettore con gli interi letti dal file:\n");
    
    for(int i=0; i<DIM; i++){
        printf("Posizione %d: [%d]\n", i, *(vettore+i));
    }
    return 0;
}