#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int next_ping = 1;
void *ping(), *pong();

void main() {
	pthread_t thread_ping, thread_pong;
	pthread_cond_init(&cond, NULL);
	
	pthread_create(&thread_ping, NULL, ping, NULL);
	pthread_create(&thread_pong, NULL, pong, NULL);

	pthread_join(thread_ping, NULL);
	pthread_join(thread_pong, NULL);
}

void *ping() {
	pthread_mutex_lock(&lock);
	while(1) {
		while(!next_ping) {
			pthread_cond_wait(&cond, &lock);
		}
		printf("Ping ");
		next_ping = 0;
		pthread_cond_signal(&cond);
	}
	pthread_mutex_unlock(&lock);
}

void *pong() {
	pthread_mutex_lock(&lock);
	while(1) {
		while(next_ping) {
			pthread_cond_wait(&cond, &lock);
		}
		printf("Pong\n");
		next_ping = 1;
		pthread_cond_signal(&cond);
	}
	pthread_mutex_unlock(&lock);
}
