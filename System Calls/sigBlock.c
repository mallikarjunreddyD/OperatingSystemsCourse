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
    
    sigset_t mask, prev_mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);

    sigprocmask(SIG_BLOCK,&mask, &prev_mask);
    printf("The code executing in this block can not be interrupted by SIGINT \n");
    sleep(20);
    sigprocmask(SIG_SETMASK,&prev_mask, NULL);    
    pause();
    return 0;
}