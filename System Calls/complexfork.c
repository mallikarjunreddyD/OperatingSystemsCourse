/* https://practicepaper.in/gate-cse/system-call */
#include<unistd.h>
int main() {
    int i;
    for(i=0;i<10;i++)
        if(i%2 == 0) fork();
    return 0;
}

/* The total number of child process created is _________*/

/*  A generalization variation
        for(i=0;i<n;i++) fork()
    This statement will create 2^n - 1 processes
*/