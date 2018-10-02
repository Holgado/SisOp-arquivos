#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define N 100



int flag[2]={0,0}; 
int turn = 0, cont = 0, i =0;
char buffer[N];


typedef struct {
	char buf[N];
	sem_t full;
	sem_t empty;
}s_buff;

s_buff shared_buffer;

void enter_item(){
	srand (time(NULL));
	char letra = 'A' + (rand() % 26);
	printf("Letra produzida %c\n", letra);
	shared_buffer.buf[] = letra;
}
void consome_item(){
	printf("Item consumido!Posição do buffer: valor do item: %c\n", it);
}

void remove_item(){
	/* int i;
    for(i = 0; shared_buffer.buf[i] != '\0'; i++)
    ;
 
    shared_buffer.buf[--i] = shared_buffer.buf[i++];*/
}

void * producer(){
	flag[0] = 1;
	turn = 1;
	char item;
	while(flag[1]==1 && turn == 1){  printf("fazendo nada prod\n");   }
	if(cont == N){
		sem_wait(&shared_buffer.full);
		printf("Produtor esperando...\n");
	}
	enter_item();
	cont++;
	if(cont == 1){			// Buffer Full
		printf("Acorda consumidor\n");
		sem_post(&shared_buffer.empty);
	}
	flag[0] = 0;
}
void * consumer(){
	flag[1] = 1;
	turn = 0;
	
	while(flag[0]==1 && turn == 0){  printf("fazendo nada cons\n");  }
	
	if(cont == 0){
		printf("Consumidor esperando...\n");
		sem_wait(&prod);
	}
	remove_item();
	cont--;
	if(cont == N-1){
		sem_post(&prod);
	}
	consome_item();
	flag[1] = 0;
}


int main(){
	pthread_t t_consumer, t_producer;
	sem_init(&prod,0,0);
	sem_init(&cons,0,0);

	pthread_create(&t_producer, NULL, producer, NULL);
	pthread_create(&t_consumer, NULL, consumer, NULL);
	pthread_exit(NULL);
	return 0;
}
