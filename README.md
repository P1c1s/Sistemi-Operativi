# Sistemi-Operativi

## Indice
1. [Files](#files)
2. [Memoria](#memoria)
3. [Fork](#fork)
4. [Thread](#thread)


- `#include <stdio.h>` libreria usata per lo standard input e output
- `fprintf(stderr, "testo")` usato per mandare sul error stream un messaggio di errore

## Files
### Sintassi  
- `#include <fcntl.h>` libreria usata per la la gestione dei files
    - `open(percorso, flags, mode)` funzione che apre un file e restuisce un file descriptor oppure -1 in caso di errore.
        - percorso:  Il percorso del file che si desidera aprire
        - flags: Un insieme di flag (sepratrati dal |) che specificano come aprire il file
            - O_RDONLY: Apri il file in sola lettura.
            - O_WRONLY: Apri il file in sola scrittura.
            - O_RDWR: Apri il file in lettura e scrittura.
            - O_CREAT: Crea il file se non esiste.
            - O_TRUNC: Se il file esiste e viene aperto in scrittura, tronca il file a zero byte.
            - O_APPEND: Scrivi i dati alla fine del file. 
        - mode: Specifica i permesssi per l'accesso al file  
    - `#include <unistd.h>` libreria usata anche per la gestione dei files
    -   `write(fileDescriptor, buffer, sizeof(...))` funzione che scrive su un file che è stato precedentente aperto e in caso di errore restituisce -1
    - `close(fileDescriptor)` funzione che chiude un file precedentemente aperto e in caso di errore restituisce -1
### Programmi

## Memoria
### Sintassi 
- `#include <stdlib.h>` libreria usata per la gestione della memoria
    - `malloc(sizeof(...))` funzione che alloca in runtime un blocco di memoria di uan specifica dimensione la memoria non è inizializzata a zero
    - `calloc(num, sizeof())` funzione che alloca in runtime un blocco di memoria di uan specifica dimensione la memoria è inizializzata a zero
    - `realloc(puntatoreNuovo, puntatoreVecchio, sizeof())` funzione che ridimensiona un blocco di memoria precedentemente allocato.
    - `free(puntatore)` funzione utilizzata per liberare la memoria precedentemente allocata dinamicamente
- `#include <string.h>` libreria per le stringhe e per la ?memoria?
    - `memset(puntatore, valore, dimensione)` funzione che sovrascrive un blocco di memoria con un valore specifico
    - `memcpy(puntatoreNuovo, puntatoreVecchio, dimensione)` funzione che copia il blocchi di memoria
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
    - `wait(NULL|&pid)` funzione che attende la terminazione di ogni processo figlio
    - `waitpid(pidDaAspettare, NULL)` funzione che attende la terminazione del processo con pid passato come argomento
### Programmi

## Thread
### Sintassi 
- `#include <pthread.h>` libreria usata per la creazione e la gestione dei processi
    - `pthread_create(&threads[i], NULL, creazioneThread, (void*)&pid)` funzione che crea un nuovo thread e restituisce 0 se l'operazione va buon fine
    - `pthread_join(threads[i], NULL)` funzione che permette al processo principale di attendere la termianzione dei thread 
    - `pthread_self()` funzione che restituisce l'id del thread
    - mutua :)
        1. `pthread_mutex_t mutex` un mutex è un meccanismo di sincronizzazione che consente di controllare l'accesso a una risorsa condivisa da parte di più thread, evitando condizioni di gara
        2. `pthread_mutex_init()` funzione che inizializza un mutex in un programma multithread
        3. `pthread_mutex_lock(&mutex)` funzione che acquisisce il mutex
        4. `pthread_mutex_unlock(&mutex)` funzione che libera il mutex
        5. `pthread_mutex_destroy()` funzione che distruggere un mutex precedentemente inizializzato con pthread_mutex_init(). È importante chiamare questa funzione quando il mutex non è più necessario, per liberare le risorse associate ad esso
### Programmi