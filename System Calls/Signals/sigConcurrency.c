#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int sig) {
    while(1) {
    printf("Handler \n");
    sleep(1);
    }    
}
int main() {
    if(signal(SIGINT,sigint_handler) == SIG_ERR)
        perror("signal error");
    
    while(1) {
    printf("main procedure \n");
    sleep(1);
    }
    
}