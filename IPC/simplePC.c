/* This is a implementation of boundedBuffer producer consumer problem.
   We will create a child process which will act as consumer.
   The parent process will act as producer.
*/
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 10
typedef struct
{
    char name[10];
    int time;
} item;
item buffer[BUFFER_SIZE];
int out = 0;
int in = 0;
void producer() {
      while (1)
        {
            item next_produced;
            snprintf(next_produced.name, sizeof(next_produced.name), "John Doe");
            next_produced.time = getTime();
            while (((in + 1) % BUFFER_SIZE) == out)
                ;
            buffer[in] = next_produced;
            in = (in + 1) % BUFFER_SIZE;
            printf("Item produced is name %s, at time %d", next_produced.name, next_produced.time);
            sleep(1);
        }
}
void consumer() {
     while (1)
        {
            sleep(3);
            item next_consumed;
            while (in == out)
                ;
            next_consumed = buffer[out];
            out = (out + 1) % BUFFER_SIZE;
            printf("Consumed Item name is %s, at time %d", next_consumed.name, next_consumed.time);
        }
}
int main()
{
    int child_pid = fork();
    if (child_pid == 0)
    {
        consumer();
    }
    else
    {
        producer();
    }
}
int getTime()
{
    time_t currentTime;
    struct tm *localTime;

    // Get the current time
    currentTime = time(NULL);

    // Convert the current time to the local time
    localTime = localtime(&currentTime);
    return asctime(localTime);
}