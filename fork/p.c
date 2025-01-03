#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>


int main(){

    int  fd = open("Pippo.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    char messaggio[] = "ciao!\n";
    int rc = fork();

    if(rc < 0){
        fprintf(stderr, "fork failed");
        exit(1);
    }

    else if(rc == 0){
        int bytes = write(fd, messaggio, sizeof(messaggio));
        if (bytes < 0)
            fprintf(stderr, "child write failed");
    }

    else{
        int bytes = write(fd, messaggio, sizeof(messaggio));
        if(bytes < 0)
            fprintf(stderr, "parent write failed");
    }

    return 0;
}