#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <string.h>

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

#define ARRAY_SIZE 1024 * 1024 * 100 // Definisce la dimensione dell'array (100MB)

typedef struct Nodo {
    int valore;
    struct Nodo* next;
} Nodo;

double tempi[10];

/* Funzione per l'accesso alla memoria */
void access_memory(int* array) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = array[i] * 2; // Accede alla memoria e modifica il valore
    }
}

/* Funzione per misurare l'accesso alla memoria primaria */
void testMemoriaPrimaria() {
    printf(BOLD_WHITE "\nMemoria primaria\n" RESET);
    int DIM = 1024 * 1024 * 10; // Dimensione di un nodo in byte
    struct timeval inizio, fine;
    gettimeofday(&inizio, NULL);
    
    Nodo* testa = (Nodo*)malloc(sizeof(Nodo));
    testa->next = NULL;

    // Allocazione di 100 milioni di nodi
    for(int i = 0; i < DIM; i++) {
        Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
        nodo->valore = rand() % 100;
        nodo->next = testa;
        testa = nodo; // Aggiorna la testa
    }

    gettimeofday(&fine, NULL);
    double tempo = (fine.tv_sec - inizio.tv_sec) + (fine.tv_usec - inizio.tv_usec) / 1000000.0;

    // Calcola la larghezza di banda
    double memoria_totale = DIM * sizeof(Nodo); // Memoria totale allocata in byte
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

/* Funzione per misurare l'accesso alla memoria primaria 2 */
void testMemoriaPrimaria2() {
    printf(BOLD_WHITE "\nMemoria primaria 2\n" RESET);
    long DIM = 1024 * 1024 * 1024; // Dimensione di 1 GB
    struct timeval inizio, fine;
    gettimeofday(&inizio, NULL);

    // Allocazione di 1 GB di memoria
    char* buffer = (char*)malloc(DIM);
    if (buffer == NULL) {
        fprintf(stderr, "Errore nell'allocazione della memoria\n");
        exit(1);
    }

    gettimeofday(&fine, NULL);
    double tempo = (fine.tv_sec - inizio.tv_sec) + (fine.tv_usec - inizio.tv_usec) / 1000000.0;

    // Calcola la larghezza di banda
    double memoria_totale = DIM; // Memoria totale allocata in byte
    double bandwidth = memoria_totale / tempo; // Larghezza di banda in byte/secondo

    // Converti la larghezza di banda in MB/s
    printf("Tempo di allocazione: %.6f secondi\n", tempo);
    printf("Larghezza di banda: %.2f MB/s\n", bandwidth / (1024 * 1024));

    free(buffer); // Libera la memoria
}

/* Funzione per misurare l'accesso alla memoria secondaria */
void testMemoriaSecondaria() {
    printf(BOLD_WHITE "\nMemoria secondaria\n" RESET);
    int DIM = 1024 * 1024 * 10;
    struct timeval inizio, fine;

    int fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (fd == -1) {
        fprintf(stderr, "Errore apertura file\n");
        exit(1);
    }

    gettimeofday(&inizio, NULL);
    for (int i = 0; i < DIM; i++) {
        char buffer = (char)(rand() % 256);
        write(fd, &buffer, sizeof(char));
    }
    gettimeofday(&fine, NULL);
    double tempo = (fine.tv_sec - inizio.tv_sec) + (fine.tv_usec - inizio.tv_usec) / 1000000.0;
    double memoria_totale = DIM * sizeof(char); // Memoria totale allocata in byte
    double bandwidth = memoria_totale / tempo; // Larghezza di banda in byte/secondo

    // Converti la larghezza di banda in MB/s
    printf("Tempo di allocazione: %.6f secondi\n", tempo);
    printf("Larghezza di banda: %.2f MB/s\n", bandwidth / (1024 * 1024));

    close(fd);
}

/* Funzione per misurare le prestazioni in TERAFLOPS */
void testTeraFlops() {
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

/* Funzione per misurare il tempo in un core */
void testSingleCore() {
    printf(BOLD_WHITE "\nSingle-core\n" RESET);
    struct timeval inizio, fine;
    gettimeofday(&inizio, NULL);
    for (int i = 0; i < 40000; i++) {
        float num = 20232413 / 232413;
    }
    gettimeofday(&fine, NULL);
    double tempo = (fine.tv_sec - inizio.tv_sec) + (fine.tv_usec - inizio.tv_usec) / 1000000.0;
    printf("Tempo: %.6f secondi\n", tempo);
}

/* Funzione per eseguire il test multi-core */
void* testMultiCore(void* arg) {
    int indice = *((int*)arg);
    struct timeval inizio, fine;
    gettimeofday(&inizio, NULL);
    for (int i = 0; i < 10000; i++) {
        float num = 20232413 / 232413;
    }
    gettimeofday(&fine, NULL);
    double tempo = (fine.tv_sec - inizio.tv_sec) + (fine.tv_usec - inizio.tv_usec) / 1000000.0;
    tempi[indice] = tempo;
    return NULL;
}

/* Funzione per il test della cache */
void cache() {
    int* array = (int*)malloc(ARRAY_SIZE * sizeof(int)); // Dichiarazione dell'array
    if (array == NULL) {
        fprintf(stderr, "Errore nell'allocazione dell'array\n");
        exit(1);
    }

    // Inizializza l'array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = 0;
    }

    // Misura il tempo di accesso alla memoria
    clock_t start = clock();
    access_memory(array);
    clock_t end = clock();

    // Calcola il tempo impiegato
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // Calcola la larghezza di banda
    double data_transferred = ARRAY_SIZE * sizeof(int); // in byte
    double bandwidth = data_transferred / time_spent; // in byte/secondo

    // Converti in gigabyte/secondo
    bandwidth /= (1024 * 1024 * 1024); // Converti in GB/s

    printf("Tempo di accesso: %.6f secondi\n", time_spent);
    printf("Larghezza di banda della cache: %.6f GB/s\n", bandwidth);

    free(array); // Libera la memoria
}

int main(int argc, char* argv[]) {
    printf(BOLD_RED "BENCHMARK ");
    printf("[PID %d]\n" RESET, getpid());

    if (argc > 1) {
        if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "-a") == 0)
            testMemoriaPrimaria();
        if (strcmp(argv[1], "-M") == 0 || strcmp(argv[1], "-a") == 0)
            testMemoriaSecondaria();
        if (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "-a") == 0)
            testTeraFlops();
        if (strcmp(argv[1], "-sc") == 0 || strcmp(argv[1], "-a") == 0)
            testSingleCore();
        if (strcmp(argv[1], "-ca") == 0 || strcmp(argv[1], "-a") == 0)
            cache();
        if (strcmp(argv[1], "-mc") == 0 || strcmp(argv[1], "-a") == 0) {
            pthread_t threads[4];
            for (int i = 0; i < 4; i++) {
                pthread_create(&threads[i], NULL, testMultiCore, (void*)&i);
            }
            for (int i = 0; i < 4; i++) {
                pthread_join(threads[i], NULL);
            }
            printf(BOLD_WHITE "\nMulti-core\n" RESET);
            for (int i = 0; i < 4; i++) {
                printf("Tempo per core %d: %.6f secondi\n", i, tempi[i]);
            }
        }
    }

    return 0;
}
