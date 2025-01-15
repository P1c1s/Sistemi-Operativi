#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


int main(){
    int pidG = getpid();

    int pid = fork();

    for (int i=1; i<=10; i++){
        if(pid>0 && i%2 != 0){
            printf("%d -> [genitore]\n", i);
        }
        else if(pid==0 && i%2 == 0){
            printf("%d -> [figlio]\n", i);
            wait(&pidG);
        }
        else if(pid<0){
            fprintf(stderr, "Errore fork\n");
            exit(1);
        }
    }
    return 0;
}