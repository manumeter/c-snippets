#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond[2];
const int pi=0, po=1;
const char *text[] = {"Ping ", "Pong\n"};

void *pipo(void* id) {
	pthread_mutex_lock(&lock);
	int me = (int)(intptr_t)id;
	int start = (me==pi);
	while(1) {
		if(start)
			start = 0;
		else
			pthread_cond_wait(&cond[me], &lock);
		printf(text[me]);
		sleep(1);
		pthread_cond_signal(&cond[!me]);
	}
	pthread_mutex_unlock(&lock);
}

void main() {
	pthread_t thread[2];
	pthread_cond_init(&cond[pi], NULL);
	pthread_cond_init(&cond[po], NULL);
	
	pthread_create(&thread[pi], NULL, pipo, (void*)(intptr_t)pi);
	pthread_create(&thread[po], NULL, pipo, (void*)(intptr_t)po);
	
	pthread_join(thread[pi], NULL);
	pthread_join(thread[po], NULL);
}
