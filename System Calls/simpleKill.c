#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include<stdlib.h>

int main() {
    int child_pid = fork();

    if(child_pid == 0) {
        while(1) {
            printf("child process is running ...\n");
            sleep(1);
        }
    } else {
        sleep(3);
        if (kill(child_pid, SIGTERM) == 0) {
            printf("Child process killed successfully.\n");
        } else {
            perror("Kill error");
        }
        wait(NULL);
        printf("parent exiting....\n");
    }
}