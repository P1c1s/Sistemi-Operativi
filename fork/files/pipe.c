#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {

    int pipefd[2]; // Array per contenere i descrittori del pipe
    pid_t pid1, pid2;

    // Creazione del pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Creazione del primo processo figlio
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Primo processo figlio
        close(pipefd[0]); // Chiudi l'estremità di lettura del pipe

        // Reindirizza l'output standard all'estremità di scrittura del pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]); // Chiudi l'estremità di scrittura originale

        // Scrivi alcuni dati sull'output standard (che vanno nel pipe)
        printf("Ciao dal primo figlio!\n");
        exit(EXIT_SUCCESS);
    }

    // Creazione del secondo processo figlio
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Secondo processo figlio
        close(pipefd[1]); // Chiudi l'estremità di scrittura del pipe

        // Reindirizza l'input standard all'estremità di lettura del pipe
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); // Chiudi l'estremità di lettura originale

        // Leggi dall'input standard (che proviene dal pipe)
        char buffer[100];
        read(STDIN_FILENO, buffer, sizeof(buffer)); // Leggi i dati dal pipe
        printf("Il secondo figlio ha ricevuto: %s", buffer);
        exit(EXIT_SUCCESS);
    }

    // Processo padre
    close(pipefd[0]); // Chiudi entrambe le estremità del pipe nel padre
    close(pipefd[1]);

    // Aspetta che entrambi i figli finiscano
    wait(NULL);
    wait(NULL);

    return 0;
}
