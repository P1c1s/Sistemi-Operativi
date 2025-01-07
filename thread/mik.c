#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 10

typedef struct stack{
        int* array;
        int capacita;
        int occupati;
}stack;

stack pila;

void init(){
        pila.array = (int*) calloc(SIZE, sizeof(int));
        pila.capacita = SIZE;
        pila.occupati = 0;
}

void push(int v){
        if(pila.occupati < pila.capacita){
                pila.array[pila.occupati] = v;
                pila.occupati++;
        }
}

int pop(){
        int ret=-1;
        if(pila.occupati>0){
                ret = pila.array[pila.occupati-1];
                pila.array[pila.occupati-1] = 0;
                pila.occupati--;
        }
        return ret;
}

void* produttore(void* arg){
        while(1){
                usleep(random()%(int)1e6);
                if(pila.occupati < pila.capacita){
                        int elementi = random()%(pila.capacita - pila.occupati);
                        for(int i=0; i<=elementi; i++){
                                int v = random();
                                push(v);
                                printf("[Produttore] Inserito %d\n", v);
                        }
                }
        }
}

void* consumatore(void* arg){

while(1){
                usleep(random()%(int)1e6);
                if(pila.occupati > 0){
                        int elementi = random() % (pila.occupati);
                        for(int i=0; i<=elementi; i++){
                                int v = pop();
                                printf("[Consumatore] Letto %d\n", v);
                        }
                }
       }
}
int main(){

        init();
        pthread_t prod, cons;

        pthread_create(&prod, NULL, produttore, NULL);
        pthread_create(&cons, NULL, consumatore, NULL);

        pthread_join(prod, NULL);
        pthread_join(cons, NULL);
}