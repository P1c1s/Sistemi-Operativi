#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <time.h>

#define RESET   "\033[0m"  // Reset del colore
#define RED     "\033[31m" // Rosso
#define GREEN   "\033[32m" // Verde
#define YELLOW  "\033[33m" // Giallo
#define BLUE    "\033[34m" // Blu
#define MAGENTA "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano
#define WHITE   "\033[37m" // Bianco

pthread_mutex_t mutex;

void* threadCheCreaProcessi(void* arg){
    int numeroProcessi = rand()%3+1;
    for(int i=0; i<numeroProcessi; i++){
        pid_t pid = fork();
        if(pid > 0){
            wait(NULL);
            printf(BLUE "[TID %ld] Sono un processo con pid %d genitore del processo %d.\n", pthread_self(), getpid(), pid);
        }else if (pid == 0)
            printf(RED "[TID %ld] Sono un processo figlio con pid %d creato dal processo %d.\n", pthread_self(), getpid(), getppid());
        else if (pid == 0){
            fprintf(stderr, "Errore fork.\n");
            exit(1);
        }
    }
}

int main(){

    printf("Programma che crea n-threads che a loro volta creano n-processi ciascuno.\n\n");

    srand(time(NULL));
    int numeroThreads = rand()%5+1;
    pthread_t threads[numeroThreads];

    pthread_mutex_init(&mutex, NULL);

    for(int i=0; i<numeroThreads; i++)
        pthread_create(&threads[i], NULL, threadCheCreaProcessi, NULL);

    for(int i=0; i<numeroThreads; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex);

    return 0;

}