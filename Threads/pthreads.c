#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

void *thread1(void *arg) { /*thread routine*/ 
    printf("Hello, world! from Thread ID %ld\n", pthread_self());
    return NULL;
}

void *thread2(void *arg) { /*thread routine*/ 
    printf("Hello, world! from Thread ID %ld\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    pthread_create(&tid1,NULL,thread1,NULL);
    pthread_create(&tid2,NULL,thread2,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    exit(0);
}

