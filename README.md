# Sistemi-Operativi

## Indice
1. [Files](#files)
2. [Memoria](#memoria)
3. [Fork](#fork)
4. [Thread](#thread)

## Files
### Sintassi  
- `#include <fcntl.h>` libreria per la la gestione dei files
    - `open()`
    - `close()`
### Programmi

## Memoria
### Sintassi 
- `#include <stdlib.h>` libreria per la gestione della memoria
    - `malloc()`
    - `calloc()`
    - `free()`
### Programmi

## Fork
### Sintassi 
- `#include <unistd.h>` libreria per la creazione e la gestione dei processi
    - `fork()` funzione che crea un processo che restituisce un intero pari al pid del processo creato
    - `getpid()` funzione che restituisce un intero pari al pid del processo corrente
    - `getppid()` funzione che restituisce un intero pari al pid genitore del processo corrente
- `#include <sys/wait.h>` per la gestione dei processi
    - `wait(NULL)` funzione che attende la terminazione di ogni processo figlio
    - `waitpid(pid)` funzione che attende la terminazione del processo con pid passato come argomento

### Programmi
Esempi con stampe dei pid dei processi genitori e figli
- Attesa
    - wait(), waitpid()


## Thread
### Sintassi 
- `#include <pthread.h>`  libreria per la creazione ela gestione dei processi
### Programmi