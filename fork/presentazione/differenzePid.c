#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){

    printf("Programma che esegue delle fork() che danno vita a dei processi\n");
    printf("che si occupano di svolgere delle differenze.\n\n");


    for(int i=0; i<=3; i++){
        printf("[%d] -> ", i);
        
        pid_t pid = fork();  
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