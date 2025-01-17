# Presentazione
Questa cartella contiene alcuni esempi pratici - riguardo i fork - finalizzati a chiarire il loro funzionamneto e a prendere dimistichezza nel loro utilizzo.

- __differenzePid.c:__  Programma che esegue delle `fork()` che danno vita a dei processi che si occupano di svolgere delle differenze.

- __forkTimer.c:__  Programma che crea più processi figli che contano fino a un numero specificato ogni processo figlio stampa il proprio PID e il numero che sta contando.

- __primaDispariPoiPari:__ Programma in cui il processo genitore stampa numeri dispari mentre il processo figlio stampa numeri pari.

- __stampa.c:__ Programma in cui il processo genitore stampa il pid del figlio - ottenuto tramite la `fork()` - e il processo figlio stampa 0 qualora il `fork()` sia andato buon fine.

- __stampaConControllo.c:__ Programma in cui il processo genitore stampa il pid del figlio - ottenuto tramite la `fork()` - e il processo figlio stampa 0 qualora il `fork()` sia andato buon fine.I due processi hanno un messaggio personalizzato grazie al controllo del pid.

- __stampaTantiFork.c:__ Programma che esegue n `fork()`, ogni `fork()` da vita ad un nuovo processo figlio che a sua volta da' vita ad nuovi processi per via delle n-1 `fork()`.



