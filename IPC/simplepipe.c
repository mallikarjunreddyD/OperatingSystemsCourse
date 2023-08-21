#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    int pipe_fd[2];
    
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }
    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        close(pipe_fd[0]); // Close read end of the pipe
        
        char message[] = "Hello from the child!";
        write(pipe_fd[1], message, strlen(message) + 1);
        
        close(pipe_fd[1]);
    } else {
        // Parent process
        close(pipe_fd[1]); // Close write end of the pipe
        
        char received_message[BUFFER_SIZE];
        read(pipe_fd[0], received_message, BUFFER_SIZE);
        printf("Received from child: %s\n", received_message);
        
        close(pipe_fd[0]);
    }
    
    return 0;
}
