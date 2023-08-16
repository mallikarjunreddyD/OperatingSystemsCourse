#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>

int main() {
   int child_pid = fork();
    int status;
    int waitStatus;
    if(child_pid == 0) {
        printf("I am child changing in to addition of two numbers process\n");
        execl("./addition","Addition program",NULL);
    } else {
        printf("Parent process: My PID is %d, Child PID is %d\n", getpid(), child_pid);
       waitStatus = wait(&status);
       printf("child exiting with status %d\n",WEXITSTATUS(waitStatus));
    }
    printf("If child executes this statement, it should be printed twice \n");
    return 1;
}