#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

pthread_mutex_t mutex;
pthread_t filosofi[5];
int stato[5] = {0, 0, 0, 0, 0};
int forchette[5] = {0, 0 , 0 , 0, 0};

void* prova(void* arg){
    int filosofo = *((int*)arg);
    while(1){
        //pthread_mutex_lock(&mutex);
        if(stato[filosofo] == 0)
            if(forchette[(filosofo+4)%5] == 0 && forchette[filosofo] == 0){
                printf("Filosofo %d sta mangiando\n", filosofo);
                pthread_mutex_lock(&mutex);
                stato[filosofo] = 1;
                forchette[(filosofo+4)%5] = 1; // forchetta sinistra
                forchette[filosofo] = 1; // forchetta destr
                usleep(1000*10*(rand()%100));
                forchette[(filosofo+4)%5] = 0;
                forchette[filosofo] = 0;
                pthread_mutex_unlock(&mutex);
            }else
                printf("Filosofo %d sta pensando\n", filosofo);

        //pthread_mutex_unlock(&mutex);
        usleep(1000*10*(rand()%100));     
    }  
    return NULL;
}

// void* prova(void* arg){
//     int filosofo = *((int*)arg);
//     while(1){
//         pthread_mutex_lock(&mutex);
//         if(stato[filosofo] == 0)
//             if(forchette[(filosofo+4)%5] == 0 && forchette[filosofo] == 0){
//                 printf("Filosofo %d sta mangiando\n", filosofo+1);
//                 stato[filosofo] = 1;
//                 forchette[(filosofo+4)%5] = 1; // forchetta sinistra
//                 forchette[filosofo] = 1; // forchetta destra
//             }else
//                 printf("Filosofo %d sta pensando\n", filosofo+1);
//         else if(stato[filosofo] == 0){
//             printf("Filosofo %d sta mangiando\n", filosofo+1);
//             stato[filosofo] = 1;
//             forchette[(filosofo+4)%5] = 1; // forchetta sinistra
//             forchette[filosofo] = 1; // forchetta destra
//         }      
//         pthread_mutex_unlock(&mutex);
//         usleep(1000*10*(rand()%100));     
//     }  
//     return NULL;
// }

int main(){
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    for(int i=0; i<5; i++){
        pthread_create(&filosofi[i], NULL, prova, (void*)&i);
        usleep(100*(rand()%100));
    }

    for(int i = 0; i<5; i++)
        pthread_join(filosofi[i], NULL);


    pthread_mutex_destroy(&mutex);

    return 0;
}