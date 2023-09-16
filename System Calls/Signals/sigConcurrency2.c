#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int count = 0;
void sigint_handler(int sig)
{
    while (count < 10)
    {
        printf("Handler count is %d \n", count);
        count++;
        sleep(1);
    }
}
int main()
{
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa,NULL) == -1)
        perror("signal error");

    while (1)
    {
        printf("main procedure count is %d\n", count);
        count++;
        sleep(1);
    }
}