#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){

    for(int i=0; i<=3; i++){
        printf("[%d] -> ", i);
        
        int pid = fork();  
        if(pid<0)
            fprintf(stderr, "Errore fork\n");
        //tutti i processi, in ordine casuale, eseguono la differenza
        printf("%d: ", abs(i-pid));
        
        //distinguo genitori e figli
        if(i != i-pid)
            printf("c'entra un genitore!\n");
        else
            printf("c'entra un figlio!\n");
    }    

    return 0;
}