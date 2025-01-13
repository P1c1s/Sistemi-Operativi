#### Esericizio 1
Scrivi un programma che chiama `fork()`. Prima di chiamare `fork()`, fai accedere il processo principale a una variabile (ad esempio, `x`) e imposta il suo valore su qualcosa (ad esempio, 100). Qual è il valore della variabile nel processo figlio? Cosa succede alla variabile quando sia il figlio che il genitore cambiano il valore di `x`?

#### Esericizio 2
Scrivi un programma che apre un file (con la chiamata di sistema `open()`) e poi chiama `fork()` per creare un nuovo processo. Può sia il figlio che il genitore accedere al descrittore di file restituito da `open()`? Cosa succede quando scrivono nel file contemporaneamente, cioè, allo stesso tempo?

#### Esericizio 3
Scrivi un altro programma utilizzando `fork()`. Il processo figlio dovrebbe stampare "hello"; il processo genitore dovrebbe stampare "goodbye". Dovresti cercare di garantire che il processo figlio stampi sempre per primo; puoi farlo senza chiamare `wait()` nel genitore?

#### Esericizio 4
Scrivi un programma che chiama `fork()` e poi chiama qualche forma di `exec()` per eseguire il programma `/bin/ls`. Vedi se riesci a provare tutte le varianti di `exec()`, inclusi (su Linux) `execl()`, `execle()`, `execlp()`, `execv()`, `execvp()`, e `execvpe()`. Perché pensi che ci siano così tante varianti della stessa chiamata di base?

#### Esericizio 5
Ora scrivi un programma che utilizza `wait()` per attendere che il processo figlio termini nel genitore. Cosa restituisce `wait()`? Cosa succede se usi `wait()` nel figlio?

#### Esericizio 6
Scrivi una leggera modifica del programma precedente, questa volta utilizzando `waitpid()` invece di `wait()`. In che caso sarebbe utile usare `waitpid()`?

#### Esericizio 7
Scrivi un programma che crea un processo figlio e poi, nel figlio, chiude l'output standard `(STDOUT_FILENO)`. Cosa succede se il figlio chiama `printf()` per stampare qualche output dopo aver chiuso il descrittore?

#### Esericizio 8
Scrivi un programma che crea due processi figli e collega l'output standard di uno all'input standard dell'altro, utilizzando la chiamata di sistema `pipe()`.