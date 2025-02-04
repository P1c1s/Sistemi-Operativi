#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int contatore = 0;

int controllo(char* originale){
	int fd = open(originale, O_CREAT | O_RDONLY, S_IRWXU);
	if(fd == -1){
		fprintf(stderr, "Errore apertura file\n");
		close(fd);
		exit(1);
	}
	char* carattere = (char*)malloc(sizeof(char));
	while(read(fd, carattere, sizeof(char)) > 0){
		contatore++;
	}
	close(fd);
}


int mycp(char* originale, char* copia){
	int fdOriginale = open(originale, O_CREAT | O_RDONLY, S_IRWXU);
	int fdCopia = open(copia, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
	if(fdOriginale == -1){
		fprintf(stderr, "Errore apertura originale\n");
		close(fdOriginale);
		exit(1);
	}
	if(fdCopia == -1){
		fprintf(stderr, "Errore apertura file copia\n");
		close(fdCopia);
		exit(1);
	}
	char* carattere = (char*)malloc(sizeof(char));

	for(int i=0; i<contatore; i++){
		read(fdOriginale, carattere, sizeof(char));
		write(fdCopia, carattere, sizeof(char));
	}
	close(fdOriginale);
	close(fdCopia);
	printf("Copia effettuata con successo\n");
}

int main(int argc, char* arg[]){

	printf("Programma che copia il contenuto di un file di testo in un altro solo se la dimensione del file è minore a 1000byte\n");
	
	if(argc == 3){
		if(controllo(arg[0]) <= 1000)
			mycp(arg[1], arg[2]);
		else
			printf("Copia non effettuata file troppo grande\n");

	}

	return 0;
  }
