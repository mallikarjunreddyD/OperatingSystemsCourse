#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

// Global variable to store the child PID
pid_t child_pid;

// Signal handler function to terminate the child process
void signal_handler(int sig) {
    printf("Parent process: Sending termination signal to the child (PID: %d)\n", child_pid);
    kill(child_pid, SIGTERM);
}

int main() {
    

    // Create a child process using fork
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        // Set up the signal handler for the termination signal (SIGUSR1)
        signal(SIGUSR1, signal_handler);
        printf("Child process: My PID is %d\n", getpid());
        // Add child process logic here

        // Child process waits for the termination signal from the parent
        while (1) {
            sleep(1); // Simulate some work
            printf("I am child and I am sleeping\n");
        }
    } else {
        // Parent process
        printf("Parent process: My PID is %d, Child PID is %d\n", getpid(), child_pid);
        
        // Wait for a moment before sending the termination signal
        sleep(5);

        // Send the termination signal to the child process using the custom signal (SIGUSR1)
        kill(child_pid, SIGUSR1);

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
