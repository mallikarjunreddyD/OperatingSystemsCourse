/* https://practicepaper.in/gate-cse/system-call */
#include<unistd.h>
int main() {
    int i;
    for(i=0;i<10;i++)
        if(i%2 == 0) fork();
    return 0;
}

/* The total number of child process created is _________*/