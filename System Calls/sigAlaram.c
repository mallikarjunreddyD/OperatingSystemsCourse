#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function for child
void child_signal_handler(int signal_number) {
    int beeps= 0;
    printf("BEEP \n");
    if (++beeps <5)  {
        printf("BEEP \n");
    } else {
        printf("BOOM! \n");
        exit(0);
    }

}

int main() {
    pid_t child_pid;

    // Fork to create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork error");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        signal(SIGALRM, child_signal_handler);

        printf("Child process (PID: %d) started.\n", getpid());
        while (1) {
            sleep(1);
        }
    } else {
        printf("Parent process (PID: %d) started.\n", getpid());
        alarm(5);
        wait(NULL);
        printf("Parent process completed.\n");
    }

    return 0;
}
