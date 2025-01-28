# Presentazione
Questa cartella contiene alcuni esempi pratici - riguardo i thread - finalizzati a chiarire il loro funzionamneto e a prendere dimistichezza nel loro utilizzo.


- __stampa.c:__ Programma che crea n thread sempre nello stesso processo che sfruttano una varibile condivisa come contatore.

- __stampaTreThread.c:__ Programma che sfrutta tre threads che stampano ognuno una lettera diversa. Notare il flusso della stampa ...

- __dueProcessi.c:__ Programma che crea due processi che sfruttano una funzione per creare tre thread ciascuno.

- __dueProcessiAvanzato.c:__ Programma che crea n thread sempre nello stesso processo che sfruttano una varibile condivisa come contatore.

- __ogniProcessoUnThread.c:__ Programma che stampa un thread con il suo ID per ognuno dei due processi.

- __threadsCreanoProcessi.c__ Programma che crea n-threads che a loro volta creano n-processi ciascuno.

- __mutex.c:__ Programma che esegue due tipologie di thread svolgono le stesse oprazioni ma in modo diverso
entrambe aggiornano il valore di due contatori con una sleep(1) in mezzo. 
    1. threadEfficente() esegue due mutex distinte distribuendo così il carico di lavoro
    2. threadNonEfficente() esegue una sola mutex aggiornando in modo sequenziale le istruzioni

- __prodConsFile.c__ Programma che crea due processi: uno scrive su un file e l'altro legge dallo stesso.

-__prodConsVettore.c__ Programma con due thread che condividono lo stesso vettore: un thread genera un numero casuale da inserire in una posizione a caso del vettore; allo stesso modo l'altro sceglie un elemento in una posizione casuale del vettore e ne azzera il valore. 