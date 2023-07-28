#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pid_t child_pid;
    char buffer[100];
    int nbytes;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Create a child process using fork
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        close(pipefd[1]); // Close the write end of the pipe since the child will only read

        // Read data from the pipe
        nbytes = read(pipefd[0], buffer, sizeof(buffer));
        if (nbytes <= 0) {
            perror("read");
            return 1;
        }

        printf("Child process (PID: %d) received data from the parent: %s\n", getpid(), buffer);

        close(pipefd[0]); // Close the read end of the pipe in the child process
    } else {
        // Parent process
        close(pipefd[0]); // Close the read end of the pipe since the parent will only write

        // Write data to the pipe
        char data[] = "Hello, child! I am your parent.";
        write(pipefd[1], data, sizeof(data));

        close(pipefd[1]); // Close the write end of the pipe in the parent process

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
