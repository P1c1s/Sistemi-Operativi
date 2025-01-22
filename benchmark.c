#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>

#define RESET   "\033[0m"  // Reset del colore
#define RED     "\033[31m" // Rosso
#define BOLD_RED     "\033[1;31m" // Rosso
#define GREEN   "\033[32m" // Verde
#define YELLOW  "\033[33m" // Giallo
#define BLUE    "\033[34m" // Blu
#define MAGENTA "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano
#define WHITE   "\033[37m" // Bianco
#define BOLD_WHITE "\033[1;37m" // Bianco in grassetto

typedef struct Nodo {
    int valore;
    struct Nodo* next;
} Nodo;

double tempi[10];

/* NOTA REFACTORING -> CREARE FUNZINE GET TEMPO*/

void testMemoriaPrimaria(){
    printf(BOLD_WHITE "\nMemoria pirmaria\n" RESET);
    int DIM = 1024*1024*10; // Dimensione di un nodo in byte
    struct timeval inizio, fine;
    gettimeofday(&inizio, NULL);
    
    Nodo* testa = (Nodo*)malloc(sizeof(Nodo));
    testa->next = NULL;

    // Allocazione di 100 milioni di nodi
    for(int i=0; i<DIM; i++) {
        Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
        nodo->valore = rand() % 100;
        nodo->next = testa;
        testa = nodo; // Aggiorna la testa
    }

    gettimeofday(&fine, NULL);
    double tempo = (fine.tv_sec - inizio.tv_sec) + (fine.tv_usec - inizio.tv_usec) / 1000000.0;

    // Calcola la larghezza di banda
    double memoria_totale = DIM*sizeof(Nodo); // Memoria totale allocata in byte
    double bandwidth = memoria_totale / tempo; // Larghezza di banda in byte/secondo

    // Converti la larghezza di banda in MB/s
    printf("Tempo di allocazione: %.6f secondi\n", tempo);
    printf("Larghezza di banda: %.2f MB/s\n", bandwidth/(1024*1024));

    // Libera la memoria
    Nodo* app;
    while (testa != NULL) {
        app = testa;
        testa = testa->next;
        free(app);
    }
}

void testMemoriaSecondaria(){
    printf(BOLD_WHITE "\nMemoria sencondaria\n" RESET);
    int DIM = 1024*1024*10;
    struct timeval inizio, fine;

    int fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if(fd == -1){
        fprintf(stderr, "Errre apertura file");
        exit(1);
        close(fd);
    }

    gettimeofday(&inizio, NULL);
    for(int i=0; i<DIM; i++){
        char buffer = (char)rand()%256;
        write(fd, &buffer, sizeof(char));
    }
    gettimeofday(&fine, NULL);
    double tempo = (fine.tv_sec - inizio.tv_sec) + (fine.tv_usec - inizio.tv_usec) / 1000000.0;
    double memoria_totale = DIM*sizeof(char); // Memoria totale allocata in byte
    double bandwidth = memoria_totale / tempo; // Larghezza di banda in byte/secondo

    // Converti la larghezza di banda in MB/s
    printf("Tempo di allocazione: %.6f secondi\n", tempo);
    printf("Larghezza di banda: %.2f MB/s\n", bandwidth/(1024*1024));


    close(fd);

}

//CHAT GPT BFF
void testTeraFlops(){
    printf(BOLD_WHITE "\nTera Flops\n" RESET);

    const long long num_operations = 1e7; // Numero ridotto di operazioni in virgola mobile
    double a = 1.0, b = 2.0, c; // Variabili in virgola mobile
    clock_t start, end;

    // Inizio del timer
    start = clock();

    // Esecuzione di operazioni in virgola mobile
    for (long long i = 0; i < num_operations; i++) {
        c = a * b; // Esempio di operazione in virgola mobile
    }

    // Fine del timer
    end = clock();

    // Calcolo del tempo impiegato
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    // Calcolo dei TERAFLOPS
    double teraflops = num_operations / time_taken / 1e12; // Convertire in TERAFLOPS

    // Stampa dei risultati
    printf("Tempo impiegato: %.6f secondi\n", time_taken);
    printf("Prestazioni: %.6f TERAFLOPS\n", teraflops);

}

void testSinglCore(){
    printf(BOLD_WHITE "\nTera Flops\n" RESET);
    for(int i=0; i<10000; i++){

    }
}

void testSingleCore(){
    printf(BOLD_WHITE "\nSingle-core\n" RESET);
    struct timeval inizio, fine;
    gettimeofday(&inizio, NULL);
    for(int i=0; i<40000; i++){
        float num = 20232413/232413;
    }
    gettimeofday(&fine, NULL);
    double tempo = (fine.tv_sec - inizio.tv_sec) + (fine.tv_usec - inizio.tv_usec) / 1000000.0;
    printf("Tempo: %2f\n", tempo);
}

void* testMultiCore(void* arg){
    int indice = *((int*)arg);
    struct timeval inizio, fine;
    gettimeofday(&inizio, NULL);
    for(int i=0; i<10000; i++){
        float num = 20232413/232413;
    }
    gettimeofday(&fine, NULL);
    double tempo = (fine.tv_sec - inizio.tv_sec) + (fine.tv_usec - inizio.tv_usec) / 1000000.0;
    tempi[indice] = tempo;
    return NULL;
}

int main(){
    printf(BOLD_RED "BENCHMARK ");
    printf("[PID %d]\n" RESET, getpid());
    testMemoriaPrimaria();
    testMemoriaSecondaria();
    testTeraFlops();
    testSingleCore();

    pthread_t threads[4];
    for(int i=0; i<4; i++)
        pthread_create(&threads[i], NULL, testMultiCore, (void*)&i);
    for(int i=0; i<4; i++)
        pthread_join(threads[i],  NULL);

    printf(BOLD_WHITE "\nMulti-core\n" RESET);
    for(int i=0; i<4; i++)
        printf("Tempo: %2f\n", tempi[i]);


    return 0;
}
