#include<stdlib.h>
#include<stdio.h>
int main() {
    int ppid = getpid();
    printf("Parent PID = %d\n",ppid);
    fork();         // A new child process is created
    printf("I will be executed twice\n");
    printf("PID=%d\n",getpid());
}


// ps -ejH  : To check all the processes in the system 
// ps -al   : To check all the user processes in the system