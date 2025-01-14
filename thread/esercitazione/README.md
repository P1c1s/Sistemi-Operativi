#### Esericizio 1
1. Il produttore, in un ciclo infinito:
    1. Deve attendere una quantità di tempo casuale inferiore al secondo
    2. Una volta scaduta l’attesa, se la pila contenuta nel file è piena, deve attendere che qualche elemento venga rimosso dal consumatore.
    3. Quando si libera dello spazio nella pila, deve inserire un numero casuale di elementi (senza andare in overflow rispetto alle dimensioni della pila) ed aggiornare il contatore all’inizio del file

2. Il consumatore, in un ciclo infinito:
    1. Deve attendere una quantità di tempo casuale inferiore al secondo
    2. Una volta scaduta l’attesa, se la pila è vuota, deve attendere che qualche elemento venga inserito dal produttore
    3. Quando la pila non è vuota, deve leggere un numero casuale di elementi (inferiore o uguale al numero di elementi presenti nello stack), sostituirne il valore con il numero 0 ed aggiornare il valore all’inizio del file.

