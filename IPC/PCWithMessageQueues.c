#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_NAME "/my_queue"
#define MAX_MESSAGES 5
#define MAX_MSG_SIZE 256

typedef struct {
    int item;
} Message;

int main() {
    mqd_t mq;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = sizeof(Message);
    attr.mq_curmsgs = 0;
    
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, &attr);
    if (mq == (mqd_t)-1) {
        perror("Queue creation failed");
        return 1;
    }
    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process (Consumer)
        for (int i = 0; i < MAX_MESSAGES; ++i) {
            Message msg;
            mq_receive(mq, (char *)&msg, sizeof(Message), NULL);
            printf("Consumed %d\n", msg.item);
        }
    } else {
        // Parent process (Producer)
        for (int i = 0; i < MAX_MESSAGES; ++i) {
            Message msg;
            msg.item = rand() % 100; // Produce an item
            mq_send(mq, (const char *)&msg, sizeof(Message), 0);
            printf("Produced %d\n", msg.item);
            sleep(1);
        }
        
        wait(NULL); // Wait for the child process to finish
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
    }
    
    return 0;
}
