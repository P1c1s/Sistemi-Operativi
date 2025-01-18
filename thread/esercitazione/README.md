#### Esericizio 1
Una pila di 10 elementi interi è condivisa tra due thread: un produttore ed un consumatore

1. Il produttore deve essere implementato secondo la seguente logica. In un ciclo infinito:
    1. Deve attendere una quantità di tempo casuale inferiore al secondo
    2. Una volta scaduta l’attesa, se la pila è piena, deve attendere che qualche elemento venga rimosso dal consumatore
    3. Quando si libera dello spazio nello stack, deve inserire un numero casuale di elementi (senza andare in overflow)

2. Il consumatore deve essere implementato secondo la seguente logica. In un ciclo infinito:
    1. Deve attendere una quantità di tempo casuale inferiore al secondo
    2. Una volta scaduta l’attesa, se lo stack è vuoto, deve attendere che qualche elemento venga inserito dal produttore
    3. Quando lo stack non è vuoto, deve leggere un numero casuale di elementi (inferiore o uguale al numero di elementi presenti nello stack) 

Suggerimenti:
Lo stack può essere implementato con un array di interi, un contatore di elementi già inseriti, e con due funzioni: `push()` e `pop()`

- Alcune funzioni utili: `random()` e `usleep()`


#### Esericizio 2
Un file su disco ha il seguente formato:
`<numero_record><record 1><record 2>`…
dove:
- `<numero_record>` è un intero rappresentante il numero di record attualmente presenti all’interno del file
- `<record1><record2>`, …, sono ognuno un numero intero.

Il file è acceduto da due thread: un produttore ed un consumatore, ed è gestito come se fosse una pila: i nuovi elementi vengono accodati al termine del file, e la lettura (con contestuale rimozione) degli elementi avviene dall’ultimo elemento del file. Il file non deve contenere più di 10 record oltre all’indicatore iniziale del numero di record presenti.

I due thread, produttore e consumatore, hanno il seguente comportamento:

1. Il produttore, in un ciclo infinito:
    1. Deve attendere una quantità di tempo casuale inferiore al secondo
    2. Una volta scaduta l’attesa, se la pila contenuta nel file è piena, deve attendere che qualche elemento venga rimosso dal consumatore.
    3. Quando si libera dello spazio nella pila, deve inserire un numero casuale di elementi (senza andare in overflow rispetto alle dimensioni della pila) ed aggiornare il contatore all’inizio del file

2. Il consumatore, in un ciclo infinito:
    1. Deve attendere una quantità di tempo casuale inferiore al secondo
    2. Una volta scaduta l’attesa, se la pila è vuota, deve attendere che qualche elemento venga inserito dal produttore
    3. Quando la pila non è vuota, deve leggere un numero casuale di elementi (inferiore o uguale al numero di elementi presenti nello stack), sostituirne il valore con il numero 0 ed aggiornare il valore all’inizio del file.

Suggerimento
Quando si esegue una `read()` o una `write()` su un file, viene spostato un cursore in avanti del numero di byte letti o scritti sul file. Ad esempio, se un file contenesse la stringa “ciaopino” e venisse effettuata una `read()` di 4 byte, questa leggerebbe “ciao”. Un’eventuale seconda `read()` di 4 byte leggerebbe invece “pino”. Allo stesso modo, se si eseguisse una prima lettura di 4 byte e successivamente una scrittura di 4 byte della stringa “anno”, il file conterrebbe la stringa “ciaoanno” al termine dell’esecuzione delle `read()` e delle `write()`.
E’ possibile spostare il cursore anche senza necessariamente effettuare una `read()` o una `write()`, utilizzando la funzione `lseek()` – usa il manuale per scoprire come usare `lseek()`.

#### Esercizio 3
Il seguente esercizio ha lo scopo di simulare lo scheduler di un sistema operativo e l’esecuzione di processi (job), nel caso semplificato in cui l’esecuzione di un processo non può essere interrotta e non è necessario accedere a risorse oltre la CPU.

Si consideri il seguente scenario. Si dispone di un computer dove:

- Il tasso di arrivi dei processi è pari a 10 processi al secondo. In altre parole, è come se venissero eseguite sul computer considerato 10 applicazioni al secondo

- Il tempo di esecuzione di ogni processo è un valore casuale sempre inferiore a 1 secondo

- Lo scheduler non supporta più di 1000 processi in coda. Ciò vuol dire che, se la coda è piena, non vengono ricevuti nuovi processi

- Lo scheduler implementa la politica FIFO

Scrivere un simulatore che implementi il comportamento dello scenario descritto e che calcoli il turnaround time medio al variare dei seguenti parametri:

- Durata della simulazione: il numero di job che arrivano all’interno del sistema è pari a 10, 20, 30.

- Numero delle CPU: il computer in considerazione può avere 1, 2, 4 CPU.

Si suggerisce di utilizzare come base di partenza l’implementazione del produttore-consumatore. La struttura dati rappresentante la coda di processi è disponibile nel file queue.h.

Suggerimenti su queue.h:

Prendere familiarità con le strutture dati definite in queue.h, in particolare con la struct Process. Quest’ultima può essere utilizzata per memorizzare informazioni utili quali l’ID del processo, il suo tempo di esecuzione, il tempo di arrivo all’interno del sistema, il tempo di avvio ed il tempo di completamento. Questa struct Process è utilizzata per costruire una lista bidirezionale che può essere acceduta con diverse funzioni, tra le quali: enqueue(Queue* queue, Process* data) e dequeue(Queue* queue): la prima aggiunge un processo in coda alla lista, la seconda rimuove e restituisce il processo in testa alla lista. Per poter inizializzare la coda è necessario utilizzare la funzione initializeQueue(Queue* queue).

Suggerimenti sulla simulazione:

E’ possibile implementare la simulazione estendendo il problema del produttore-consumatore, in particolare:

- Il thread produttore può essere implementato in modo tale da generare processi alla velocità indicata in precedenza

- Il thread consumatore può rappresentare una CPU che estrae un processo dalla coda e lo esegue.

#### Esercizio 4
Da Wikipedia (https://it.wikipedia.org/wiki/Problema_dei_filosofi_a_cena):

Cinque filosofi siedono ad una tavola rotonda con un piatto di spaghetti davanti e una forchetta a sinistra. Ci sono dunque cinque filosofi, cinque piatti di spaghetti e cinque forchette.

Si immagini che la vita di un filosofo consista di periodi alterni di mangiare e pensare, e che ciascun filosofo abbia bisogno di due forchette per mangiare, ma che le forchette vengano prese una per volta. Dopo essere riuscito a prendere due forchette il filosofo mangia per un po', poi lascia le forchette e ricomincia a pensare. Il problema consiste nello sviluppo di un algoritmo che impedisca lo stallo (deadlock) o la morte d'inedia (starvation). Il deadlock può verificarsi se ciascuno dei filosofi tiene in mano una forchetta senza mai riuscire a prendere l'altra. Il filosofo F1 aspetta di prendere la forchetta che ha in mano il filosofo F2, che aspetta la forchetta che ha in mano il filosofo F3, e così via in un circolo vizioso. La situazione di starvation può verificarsi indipendentemente dal deadlock se uno dei filosofi non riesce mai a prendere entrambe le forchette.

Implementare un programma basato sulla libreria pthread dove i cinque filosofi sono realizzati tramite 5 thread, e si cerchi di evitare situazioni di deadlock e starvation. Su Wikipedia è presente anche una possibile soluzione, ma vi chiedo di leggerla soltanto dopo aver riflettuto un po'.