#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 5

typedef struct {
    int buffer[BUFFER_SIZE];
    int in, out;
} SharedBuffer;

int main() {
    const char *SHARED_MEM_NAME = "/my_shared_memory";
    const int SHARED_MEM_SIZE = sizeof(SharedBuffer);
    //Create a shared-memory object 
    int shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Shared memory creation failed");
        return 1;
    }
    // Truncate the object to configure the size of the object in bytes
    if (ftruncate(shm_fd, SHARED_MEM_SIZE) == -1) {
        perror("Truncation of shared memory failed");
        return 1;
    }
    // Establish a memory mapped file containing the shared-memory object.
    SharedBuffer *shared_buffer = mmap(NULL, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_buffer == MAP_FAILED) {
        perror("Mapping shared memory failed");
        return 1;
    }
    
    shared_buffer->in = shared_buffer->out = 0;
    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process (Consumer)
        while (1) {
            while (shared_buffer->in == shared_buffer->out); // Wait if buffer is empty
            int item = shared_buffer->buffer[shared_buffer->out];
            shared_buffer->out = (shared_buffer->out + 1) % BUFFER_SIZE;
            printf("Consumed %d\n", item);
        }
    } else {
        // Parent process (Producer)
        while (1) {
            int item = rand() % 100; // Produce an item            
            while (((shared_buffer->in + 1) % BUFFER_SIZE) == shared_buffer->out); // Wait if buffer is full            
            shared_buffer->buffer[shared_buffer->in] = item;
            shared_buffer->in = (shared_buffer->in + 1) % BUFFER_SIZE;
            printf("Produced %d\n", item);
            sleep(1);
        }
    }
    
    munmap(shared_buffer, SHARED_MEM_SIZE);
    shm_unlink(SHARED_MEM_NAME);
    
    return 0;
}
