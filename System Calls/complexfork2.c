/*https://practicepaper.in/gate-cse/system-call */

#include<unistd.h>
int main() {
    fork();
    fork();
    printf("yes");
    return 0;
}

/*how many times the string yes will be printed?*/