##### Esericizio 1
Allocazione di memoria dinamica
Scrivi un programma che crea un array dinamico di numeri interi di dimensione specificata dall'utente, riempie l'array con numeri casuali e stampa l'array. Assicurati di liberare la memoria allocata alla fine del programma.

##### Esericizio 2
Gestione di vettori dinamici
Implementa una struttura dati per un vettore dinamico di interi. Includi funzioni per aggiungere un elemento, rimuovere un elemento e stampare tutti gli elementi del vettore. Assicurati che il vettore aumenti la sua capacità quando necessario.

##### Esericizio 3
Manipolazione della memoria
Scrivi un programma che alloca memoria per un array di interi, usa memset per impostare tutti gli elementi a zero, quindi usa memcpy per copiare il contenuto di un altro array nella memoria appena allocata.

##### Esericizio 4
Implementazione di my_malloc() e my_free()
Scrivi un programma che implementi le funzioni my_malloc() e my_free(). Queste funzioni devono comportarsi rispettivamente come le funzioni malloc() e free(), cioè: la prima deve ritornare un puntatore void ad una area di memoria utilizzabile della dimensione specificata come parametro; la seconda deve liberare l'area di memoria alla quale fa riferimento il puntatore passato come parametro. L'intero programma deve essere realizzato senza utilizzare le funzioni malloc() e free(). E' possibile utilizzare una sola volta mmap() e munmap(), per le quali sono disponibili le pagine di man.