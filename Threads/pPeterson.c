#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

int Turn;
int Flag[2]; 
void *producer(void *arg) { /*thread routine*/ 
    while(1) {
		Flag[0] = 1;
		Turn = 1;
		while(Flag[1] && Turn == 1) {
			printf("Producer: Waiting to enter critical section \n");
		}
		printf("Producer: Entering critical section \n");
		sleep(3);
		printf("Producer: Exiting critical section \n");
		Flag[0] = 0;
		sleep(2);
	}
    return NULL;
}

void *consumer(void *arg) { /*thread routine*/ 
    while(1) {
		Flag[1] = 1;
		Turn = 0;
		while(Flag[0] && Turn == 0) {
			printf("Consumer: Waiting to enter critical section\n");
		}
		printf("Consumer: Entering critical section \n");
		sleep(10);
		printf("Consumer: Exiting critical section\n");
		Flag[1] = 0;
		sleep(2);
	}
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    Flag[0] = 0;
	Flag[1] = 0;

    pthread_create(&tid1,NULL,producer,NULL);
    pthread_create(&tid2,NULL,consumer,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    exit(0);    
	
}

