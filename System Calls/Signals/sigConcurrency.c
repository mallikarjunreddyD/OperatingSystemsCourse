#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int count = 0;
void sigint_handler2(int sig) {
    while(count< 10) {
    printf("inner Handler count is %d \n",count);
    count++;
    sleep(1);
    }    
}
void sigint_handler(int sig) {
    if(signal(SIGINT,sigint_handler2) == SIG_ERR)
        perror("signal error");    
    while(count< 10) {
    printf("Outer Handler count is %d \n",count);
    count++;
    sleep(1);
    }    
}

int main() {
    if(signal(SIGINT,sigint_handler) == SIG_ERR)
        perror("signal error");
    
    while(1) {
    printf("main procedure count is %d\n",count);
    count++;
    sleep(1);
    }
    
}