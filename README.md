# Sistemi-Operativi

## Indice
- [Sistemi-Operativi](#sistemi-operativi)
  - [Indice](#indice)
  - [Files](#files)
  - [Memoria](#memoria)
  - [Fork](#fork)
  - [Thread](#thread)

## Files
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
    -   `read(fileDescriptor, buffer, sizeof(...))`
    funzione che legge da un file che è stato precedentemente aperto e in caso di errore restituisce -1
    - `close(fileDescriptor)` funzione che chiude un file precedentemente aperto e in caso di errore restituisce -1

## Memoria
- `#include <stdlib.h>` libreria usata per la gestione della memoria
    - `malloc(sizeof(...))` funzione che alloca in runtime un blocco di memoria di uan specifica dimensione la memoria non è inizializzata a zero
    - `calloc(num, sizeof())` funzione che alloca in runtime un blocco di memoria di uan specifica dimensione la memoria è inizializzata a zero
    - `realloc(puntatoreNuovo, puntatoreVecchio, sizeof())` funzione che ridimensiona un blocco di memoria precedentemente allocato.
    - `free(puntatore)` funzione utilizzata per liberare la memoria precedentemente allocata dinamicamente
- `#include <string.h>` libreria per le stringhe e per la ?memoria?
    - `memset(puntatore, valore, dimensione)` funzione che sovrascrive un blocco di memoria con un valore specifico
    - `memcpy(puntatoreNuovo, puntatoreVecchio, dimensione)` funzione che copia i blocchi di memoria
- `#include <sys/mman.h>` libreria usata per la gestione della memoria
    - `mmap(indirizzoDesiderato, dimensione, protezione, flags, fileDescriptior, offset)` funzione che mappa dei blocchi di memoria, utilizzata solitamente per mappare i file.
      - indirizzoDesiderato: indirizzo di memoria da cui si vuole iniziare a mappare, NULL se si lascia fare al sistema operativo
      - dimensione: dimensione di memoria che vogliamo mappare
      - protezione: specificano i permessi di lettura e scrittura per la porzione di memoria interessata
        - PROT_NONE: non è possibile accedere alla pagina 
        - PROT_READ: è possibile leggere la pagina
        - PROT_WRITE: è possibile scrivere sulla pagina
        - PROT_EXEC: è possibile eseguire la pagina
      - flags: specifica informazioni aggiuntive
        - MAP_ANONYMOUS o MAP_ANON: si mappa una porzione di memoria non legata ad un file. L'offset viene ignorato
        - MAP_FILE: si mappa regolarmente un file
        - MAP_FIXED: non permette al sistema di selezionare un indirizzo di memoria diverso da quello specificato
        - MAP_PRIVATE: le modifiche sono private
        - MAP_SHARED: le modifiche sono condivise
      - fileDescriptor: riferimento al file se se ne vuole mappare uno, -1 altrimenti
      - offset: offset della porzione di file da mappare rispetto all'inizio del file stesso
    - `munmap(puntatore, dimensione)` libera la dimensione di memoria specificata a partire dall'indirizzo indicato dal puntatore  

## Fork
- `#include <unistd.h>` libreria usata per la creazione e la gestione dei processi oppure per l'esecuzione di comandi della console
    - `fork()` funzione che crea un processo che restituisce un intero pari al pid del processo creato
    - `getpid()` funzione che restituisce un intero pari al pid del processo corrente
    - `getppid()` funzione che restituisce un intero pari al pid genitore del processo corrente
    - `exec` la classe di funzioni exec permette di eseguire dei comandi della shell all'interno del programma C. La sequenza passata alla funzione deve sempre terminare con NULL, che la exec sia in forma di liste o vettoiale.
      - `execl(path, comando, argomento1, argomento2, NULL)` permette di eseguire il file/comando presente nel path specificato, passando gli argomenti scandendoli uno per uno
      - `execlp(comando, comando, argomento1, argomento2, NULL)` permette di eseguire il file/comando specificato come primo e secondo argomento senza specificare il percorso del comando perché viene preso dalla variabile d'ambiente PATH
      - `execle(path, comando, argomento1, argomento2, NULL, env[])` permette si eseguire il comando specificato come secondo argomento presente al path del primo argomento potendo specificare le variabili d'ambiente dove cercare il comando in un vettore che termina con NULL
      - `execv(path, args[]);` simile al execl ma anziché passare gli argomenti enumerandoli, vengono passati all'interno di un vettore che termina con un NULL
      - `execvp(args[0], args[]);` simile al execlp ma gli argomenti vengono passati all'interno di un vettore che termina con un NULL
      - `execvpe(args[0], args[], env[])` simile ad execle, gli argomenti sono passati in un vettore che termina cono NULL. Cerca il comando all'interno della variabile d'ambiente PATH del sistema che esegue il programma
- `#include <sys/wait.h>` per la gestione dei processi
    - `wait(NULL|&pid)` funzione che attende la terminazione di ogni processo figlio
    - `waitpid(pidDaAspettare, NULL)` funzione che attende la terminazione del processo con pid passato come argomento

## Thread
- `#include <pthread.h>` libreria usata per la creazione e la gestione dei processi
    - `pthread_create(&threads[i], NULL, creazioneThread, (void*)&pid)` funzione che crea un nuovo thread e restituisce 0 se l'operazione va buon fine
    - `pthread_join(threads[i], NULL)` funzione che permette al processo principale di attendere la termianzione dei thread 
    - `pthread_self()` funzione che restituisce l'id del thread
    - mutua :)
        1. `pthread_mutex_t mutex` un mutex è un meccanismo di sincronizzazione che consente di controllare l'accesso a una risorsa condivisa da parte di più thread, evitando condizioni di gara
        2. `pthread_mutex_init(&mutex, NULL)` funzione che inizializza un mutex in un programma multithread
        3. `pthread_mutex_lock(&mutex)` funzione che acquisisce il mutex
        4. `pthread_mutex_unlock(&mutex)` funzione che libera il mutex
        5. `pthread_mutex_destroy(&mutex)` funzione che distruggere un mutex precedentemente inizializzato con pthread_mutex_init(). È importante chiamare questa funzione quando il mutex non è più necessario, per liberare le risorse associate ad esso