#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    int didChild;
    int status;

    int wait_pid;

    didChild = fork();
    if (didChild == -1)
    {
        printf("child creation failed\n");
        return 1;
    }
    else if (didChild == 0)
    {
        printf("Child process: PID is %d\n", getpid());
        sleep(5);
        printf("Child exiting\n");
        exit(0);
    }
    else
    {
        printf("Parent process: PID is %d\n", getpid());
        // wait for child to terminate
        wait_pid = wait(&status);
        if (wait_pid == -1)
        {
            printf("error on wait");
            return -1;
        }
        // check whether the child process exitid normally
        if (WIFEXITED(status))
        {
            // extract the exit status of the terminated child
            int exit_status = WEXITSTATUS(status);
            printf("Child process %d exited with status %d", wait_pid, exit_status);
        } 
        printf("parent exiting\n");
    }
}