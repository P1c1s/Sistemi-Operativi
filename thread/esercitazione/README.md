#### Esericizio 1
Il produttore, in un ciclo infinito:
Deve attendere una quantità di tempo casuale inferiore al secondo
Una volta scaduta l’attesa, se la pila contenuta nel file è piena, deve attendere che qualche elemento venga rimosso dal consumatore  Quando si libera dello spazio nella pila, deve inserire un numero casuale di elementi (senza andare in overflow rispetto alle dimensioni della pila) ed aggiornare il contatore all’inizio del file

#### Esericizio 2
Il consumatore, in un ciclo infinito:
Deve attendere una quantità di tempo casuale inferiore al secondo
Una volta scaduta l’attesa, se la pila è vuota, deve attendere che qualche elemento venga inserito dal produttore
Quando la pila non è vuota, deve leggere un numero casuale di elementi (inferiore o uguale al numero di elementi presenti nello stack), sostituirne il valore con il numero 0 ed aggiornare il valore all’inizio del file.

