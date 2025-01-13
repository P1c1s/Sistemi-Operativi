# Sistemi-Operativi

## Indice
1. [Files](#files)
2. [Memoria](#memoria)
3. [Fork](#fork)
4. [Thread](#thread)

## Files
### Sintassi  
- `#include <fcntl.h>` libreria usata per la la gestione dei files
    - `open()`
    - `close()`
    - `fprintf(stderr, "testo")` usato per mandare sul error stream un messaggio di errore 
### Programmi

## Memoria
### Sintassi 
- `#include <stdlib.h>` libreria usata per la gestione della memoria
    - `malloc()` funzione che alloca in runtime un blocco di memoria di uan specifica dimensione la memoria non è inizializzata a zero
    - `calloc()` funzione che alloca in runtime un blocco di memoria di uan specifica dimensione la memoria è inizializzata a zero
    - `realloc()`
    - `free()` funzione utilizzata per liberare la memoria precedentemente allocata dinamicamente
- `#include <string.h>` libreria per le stringhe e per la ?memoria?
    - `memset(vettore, valore, dimensione)` - funzione che sovrascrive un blocco di memoria con un valore specifico
    - `memcpy(vettoreNuovo, vettoreVecchio, dimensione)` funzione che copia il blocchi di memoria
- `#include <sys/mman.h>` libreria usata per la gestione della memoria
    - `mmap()`
    - `munmap`  

### Programmi

## Fork
### Sintassi 
- `#include <unistd.h>` libreria usata per la creazione e la gestione dei processi oppure per l'esecuzione di comandi della console
    - `fork()` funzione che crea un processo che restituisce un intero pari al pid del processo creato
    - `getpid()` funzione che restituisce un intero pari al pid del processo corrente
    - `getppid()` funzione che restituisce un intero pari al pid genitore del processo corrente
    - `execl("/usr/bin/echo", "echo", "Ciao sono il processo genitore che usa ECHO", NULL);`
    - `execve(?)`
    - `execvp(args[0], args);`
    - `execvpe(?);`


- `#include <sys/wait.h>` per la gestione dei processi
    - `wait(NULL)` funzione che attende la terminazione di ogni processo figlio
    - `waitpid(pid)` funzione che attende la terminazione del processo con pid passato come argomento

### Programmi
Esempi con stampe dei pid dei processi genitori e figli
- Attesa
    - wait(), waitpid()


## Thread
### Sintassi 
- `#include <pthread.h>` libreria usata per la creazione e la gestione dei processi
### Programmi