#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


#define NUM_THREADS 8
#define NUMERO 1000000

void* multiThread(void* arg){
    struct timeval start, end;
    gettimeofday(&start, NULL);
    int indice = *((int*)arg);
    int min = *((int*)arg+1);
    int max = *((int*)arg+2);
    int esiste = 0;

    for(int num=min; num<max; num++){
        for(int i=2; i<num && !esiste; i++)
            if(num%i == 0)
                esiste = 1;
        if(esiste != 0)
            esiste = 0;
        //Se su vuole vedere la stampa dei numeri primi togliere i commenti
        // else
        //     printf("%d ", num);
    }
    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("[THREAD %d] Tempo parziale di esecuzione: %f secondi\n", indice, time_taken);
}

void singleThread(int numero){
    int esiste = 0;

    for(int num=0; num<numero; num++){
        for(int i=2; i<num && !esiste; i++)
            if(num%i == 0)
                esiste = 1;
        if(esiste != 0)
            esiste = 0;
        //Se su vuole vedere la stampa dei numeri primi togliere i commenti
        // else
        //     printf("%d ", num);
    }
}

int main(){

    printf("Programma che esegue dei calcoli in parallelo ed in serie.\n\n");
    
    struct timeval start, end;
    int N = NUMERO/20;
    int vettore1[3] = {1, 2, 6*N};
    int vettore2[3] = {2, 6*N, 10*N};
    int vettore3[3] = {3, 10*N, 12*N};
    int vettore4[3] = {4, 12*N, 14*N};
    int vettore5[3] = {5, 14*N, 16*N};
    int vettore6[3] = {6, 16*N, 18*N};
    int vettore7[3] = {7, 18*N, 19*N};
    int vettore8[3] = {8, 19*N, 20*N};

    pthread_t threads[NUM_THREADS];

    /* CALCOLO IN PARALLELO*/

    // Inizio del tempo
    gettimeofday(&start, NULL);

    pthread_create(&threads[0], NULL, multiThread, (void*)&vettore1);
    pthread_create(&threads[1], NULL, multiThread, (void*)&vettore2);
    pthread_create(&threads[2], NULL, multiThread, (void*)&vettore3);
    pthread_create(&threads[3], NULL, multiThread, (void*)&vettore4);
    pthread_create(&threads[4], NULL, multiThread, (void*)&vettore5);
    pthread_create(&threads[5], NULL, multiThread, (void*)&vettore6);
    pthread_create(&threads[6], NULL, multiThread, (void*)&vettore7);
    pthread_create(&threads[7], NULL, multiThread, (void*)&vettore8);

    for(int i=0; i<NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    // Fine del tempo
    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("[CON THREADS] Tempo complessivo di esecuzione: %f secondi\n", time_taken);

    /* CALCOLO IN PARALLELO*/

    // Inizio del tempo
    gettimeofday(&start, NULL);
    
    singleThread(NUMERO);
    
    // Fine del tempo
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("[SENZA THREADS] Tempo di esecuzione: %f secondi\n", time_taken);

    return 0;

}