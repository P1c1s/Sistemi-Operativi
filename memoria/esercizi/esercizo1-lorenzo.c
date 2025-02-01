#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>

typedef struct Pila{
    int valore;
    struct Pila* next;
} Pila;

Pila* push(Pila* testa){

    Pila* p = (Pila*)mmap(NULL, sizeof(Pila), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    p->valore = rand()%100;
    p->next = NULL;

    if(testa != NULL)
        p->next = testa;

    return p;
}

Pila* pop(Pila* testa){
    if(testa != NULL)
        testa = testa->next;
    return testa;
}

void stampa(Pila* p) {
    if (p == NULL) {
        printf("La pila è vuota.\n");
        return;
    }

    printf("Contenuto della pila: ");
    while (p != NULL) {
        printf("%d ", p->valore);
        p = p->next;
    }
    printf("\n");
}


int main(){
    srand(time(NULL));
    Pila* testa = NULL;
    int comando;
    printf("Programma che...");
    do{ 
        printf("\n\n1) Aggiungi elemento\n");
        printf("2) Rimuovi elemento\n");
        printf("3) Stampa pila\n");
        printf("comando: ");
        scanf("%d", &comando);
        if(comando == 1)
            testa = push(testa);
        else if(comando == 2)
            testa = pop(testa);
        else if(comando == 3)
            stampa(testa);
        else if(comando == 0)
            printf("Ciao ciao\n");
        else
            printf("Comando non trovato\n");
    }while(comando != 0);

    return 0;

}