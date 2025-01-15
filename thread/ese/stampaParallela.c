#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct{
	int r;
	char c;
	}param;

char vincitore=0;

void *cavallo(void *arg){
	
	int cl,rg;
	char ch;
	param *p;
	p=(param *) arg;
	rg=p->r++;
	ch=p->c++;
	
	for(cl=0;cl<30;cl++){
		
		printf("\033[%d;%dH%c",rg,cl,ch);
		fflush(stdout);
		sleep(rand()%2);
	}
	
	if(vincitore==0) vincitore=ch;
	
	pthread_exit(0);
	}


int main(int argc, char **argv)
{
	pthread_t t[20];
	int i;
	param *p;
	p=malloc(sizeof(param));
	p->r=1;
	p->c='A';
	for(i=0;i<20;i++){
		pthread_create(&t[i],NULL,cavallo,p);
		}
		
	for(i=0;i<20;i++){
		pthread_join(t[i],NULL);
	}
	printf("Vincitore : %c\n",vincitore);
	return 0;
}