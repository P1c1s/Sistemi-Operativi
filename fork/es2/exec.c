#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    int pid = fork();
    
    if(pid>0){
        wait(NULL);
        execl("/usr/bin/echo", "", "Ciao sono il processo genitore che usa ECHO", NULL);
    }else if(pid==0){
        execl("/usr/bin/echo", "", "Ciao sono il figlio del processo genitore che usa ECHO, e ho la precedenza", NULL);
    }

    //execl("/bin/ls", "ls", NULL);
    return 0; 
}