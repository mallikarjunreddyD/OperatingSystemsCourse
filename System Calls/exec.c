#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include<stdlib.h>

// Signal handler function for the child process
void child_signal_handler(int sig) {
    printf("Child process (PID: %d) received signal (SIGUSR1). Execution addition program...\n", getpid());
    
    //Execute the addition program
    if(execl("./addition","Addition program",NULL) == -1) {
        printf("execl error");
        exit(1);
    }
}

int main() {
    pid_t child_pid;
    struct sigaction sa;

    // Create a child process using fork
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        printf("Child process: My PID is %d\n", getpid());

        // Set up the signal handler for the child process to catch SIGUSR1
        sa.sa_handler = child_signal_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;

        if (sigaction(SIGUSR1, &sa, NULL) == -1) {
            perror("sigaction");
            return 1;
        }
        // Child process waits for the signal from the parent
        sleep(100);
    } else {
        // Parent process
        printf("Parent process: My PID is %d, Child PID is %d\n", getpid(), child_pid);

        // Wait for a moment before sending the signal
        sleep(5);

        // Send the signal (SIGUSR1) to the child process
        printf("Parent process: Sending signal (SIGUSR1) to the child (PID: %d)\n", child_pid);
        if (kill(child_pid, SIGUSR1) == -1) {
            perror("kill");
            return 1;
        }

        // Wait for the child process to terminate
        int status;
        if (wait(&status) != -1) {
            if (WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
                printf("Child process %d exited with status %d\n", child_pid, exit_status);
            }
        }
    }

    return 0;
}
