#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void sigint_handler(int sig) {
    printf("SO you think you can stop the bomb with ctrl-c, do you? \n");
    sleep(2);
    printf("Well....");
    fflush(stdout);
    sleep(1);
    printf("OK. :-) \n");
    exit(0);
}
int main() {
    if(signal(SIGINT,sigint_handler) == SIG_ERR)
        perror("signal error");
    
    pause();
    return 0;
}