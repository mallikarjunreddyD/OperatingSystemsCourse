#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main() {
    int didChild;
    didChild = fork();
    if (didChild == -1) {
        printf("child creation failed\n");
        return 1;
    } else if (didChild == 0) {
        printf("Child process: PID is %d\n",getpid());
        sleep(5);
        printf("Child exiting\n");
    } else {
        printf("Parent process: PID is %d\n",getpid());
        printf("parent exiting\n");
    }
}