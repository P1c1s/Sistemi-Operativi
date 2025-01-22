#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<string.h>

#define DIM 20

int main(){

    srand(time(NULL));
    int fd = open("Pippo2.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    if (fd == -1){
        fprintf(stderr, "Error while opening the file\n");
        exit(1);
    }

    for(int i=0; i<DIM; i++){
        int numero = rand()%500;
        char stringa[5];
        sprintf(stringa, "%d\n", numero);
        write(fd, stringa, strlen(stringa));
    }

    close(fd);

    fd = open("Pippo2.txt", O_CREAT | O_RDONLY, S_IRWXU);
    if (fd == -1){
        fprintf(stderr, "Error while opening the file");
        exit(1);
    }
    char* singleChar = (char*) malloc(sizeof(char));
    char* stringNum = (char*) calloc(5, sizeof(char));

    while(read(fd, singleChar, sizeof(char)) != 0){
        if (*singleChar == '\n'){
            printf("%d\n", atoi(stringNum));
            memset(stringNum, 0, 5*sizeof(char));
        }
        else{
            strcat(stringNum, singleChar);
        }
    }

    close(fd);
    return 0;
}
