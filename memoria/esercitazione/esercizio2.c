#include <stdio.h>
#include <stdlib.h>

void stampa(int* vettore, int dimensione){
    printf("[ ");
    for(int i=0; i<dimensione; i++){
        printf("%d ", *(vettore+i));
    }
    printf("]");
}

int* aggiungiElemento(int* vettore, int *dimensione){
    *dimensione=*dimensione+1;
    vettore = (int*)realloc(vettore, (*dimensione)*sizeof(int));
    if(vettore == NULL){
        fprintf(stderr, "Errore");
        exit(1);
    }
    printf("Inserisci numero: ");
    scanf("%d", &vettore[*dimensione-1]);
    return vettore;
}

int* aggiungiElementi(int* vettore, int *dimensione){
    int vecchiaDimensione = (*dimensione);
    int n = 0;
    printf("Quanti numeri vuoi inserire? ");
    scanf("%d", &n);
    *dimensione=(*dimensione)+n;
    vettore = (int*)realloc(vettore, (*dimensione)*sizeof(int));
    if(vettore == NULL){
        fprintf(stderr, "Errore");
        exit(1);
    }
    for(int i=vecchiaDimensione; i<(*dimensione); i++){
        printf("Iserisci %d° numero: ", i-vecchiaDimensione+1);
        scanf("%d", &vettore[i]);
    }
    return vettore;
}

int* rimuoviElementoInCoda(int* vettore, int *dimensione){
    *dimensione = (*dimensione)-1;
    vettore = (int*)realloc(vettore, (*dimensione)*sizeof(int));
    if(vettore == NULL){
        fprintf(stderr, "Errore");
        exit(1);
    }
    return vettore;
}

int main(){

    printf("Programma che crea un vettore di dimenione variabile.\n\n");

    int dimensione = 0;
    int comando;
    int *vettore = (int*)malloc(dimensione* sizeof(int));

    do{
        printf("\n\n----------Menu'----------\n");   
        printf("1) Inserimento numero\n");
        printf("2) Inserimento piu' numeri\n");
        printf("3) Eliminazione\n");
        printf("4) Stampa\n");
        printf("0) Esci\n");
        printf("comando atteso: ");
        scanf("%d", &comando);
        if(comando == 1)
            vettore = aggiungiElemento(vettore, &dimensione);
        else if(comando == 2)
            vettore = aggiungiElementi(vettore, &dimensione);
        else if(comando == 3)
            vettore = rimuoviElementoInCoda(vettore, &dimensione);
        else if(comando == 4)
            stampa(vettore, dimensione);
    }while(comando != 0);

    free(vettore);
    printf("Memoria liberata.\n");

    return 0;

}