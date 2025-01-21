#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define RESET   "\033[0m"  // Reset del colore
#define RED     "\033[31m" // Rosso
#define GREEN   "\033[32m" // Verde
#define YELLOW  "\033[33m" // Giallo
#define BLUE    "\033[34m" // Blu
#define MAGENTA "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano
#define WHITE   "\033[37m" // Bianco

typedef struct Nodo {
    int valore;
    struct Nodo* next;
} Nodo;

void testMemoria() {
    int DIM = 1024 * 1024; // Dimensione di un nodo in byte
    struct timeval inizio, fine;
    gettimeofday(&inizio, NULL);
    
    Nodo* testa = (Nodo*)malloc(sizeof(Nodo));
    testa->next = NULL;

    // Allocazione di 100 milioni di nodi
    for (int i = 0; i < (1024 * 1024 * 100); i++) {
        Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
        nodo->valore = rand() % 100;
        nodo->next = testa;
        testa = nodo; // Aggiorna la testa
    }

    gettimeofday(&fine, NULL);
    double tempo = (fine.tv_sec - inizio.tv_sec) + (fine.tv_usec - inizio.tv_usec) / 1000000.0;

    // Calcola la larghezza di banda
    double memoria_totale = (1024 * 1024 * 100) * sizeof(Nodo); // Memoria totale allocata in byte
    double bandwidth = memoria_totale / tempo; // Larghezza di banda in byte/secondo

    // Converti la larghezza di banda in MB/s
    printf("Tempo di allocazione: %.6f secondi\n", tempo);
    printf("Larghezza di banda: %.2f MB/s\n", bandwidth / (1024 * 1024));

    // Libera la memoria
    Nodo* app;
    while (testa != NULL) {
        app = testa;
        testa = testa->next;
        free(app);
    }
}

int main() {
    printf(RED "BENCHMARK\n\n" RESET);
    testMemoria();
    return 0;
}
