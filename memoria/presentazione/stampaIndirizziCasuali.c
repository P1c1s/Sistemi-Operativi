#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    printf("Programma che stampa gli indirizzi di memoria di 10 allocazioni.\n\n");
    srand(time(NULL));
 
    printf("    &intero    | &(*intero) | Valore\n");
    printf("------------------------------------\n");
    for(int i=0; i<10; i++){
        int* intero = (int*)malloc(sizeof(int));
        *intero = rand()%1000;
        printf("%p | %p | %d\n", &intero, &(*intero), *intero);
        //Se viene fatta la free(intero) l'indirizzo &(*intero) non cambia ma rimane sempre lo stesso
        //free(intero);        
    }

    return 0;
}


