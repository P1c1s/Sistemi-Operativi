#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
int contatore = 0;

void* calcolatore(void* arg){
	int num = *((int*)arg);
	int primo = 0;
	for(int i=2; i<num-1 && !primo; i++)
		if(num%i == 0)
			primo = 1;
	if(primo == 0){
		pthread_mutex_lock(&mutex);
		contatore++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(int argc, char* arg[]){

	printf("Programma che riceve in input 4 numeri e ne verifica la primalità\n");
	printf("E' parametrico, si possono passare da uno a N numeri\n\n");
	pthread_mutex_init(&mutex, NULL);
	pthread_t threads[argc-1];

	if(argc > 1){
		int numeri[argc-1];
		for(int i=0; i<argc-1; i++){
			numeri[i] = atoi(arg[i+1]);
			pthread_create(&threads[i], NULL, calcolatore, (void*)&numeri[i]);
		}

		for(int i=0; i<argc-1; i++)
			pthread_join(threads[i], NULL);
		printf("Mi hai fornito %d numeri primi\n", contatore);
	}else
		printf("Passami almeno un numero\n");

	pthread_mutex_destroy(&mutex);
	return 0;
}