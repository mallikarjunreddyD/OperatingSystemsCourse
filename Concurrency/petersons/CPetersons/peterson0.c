
#include "globals.c"
#include<stdbool.h>
#include<stdio.h>
int main() {
flag[0] = false;
flag[1] = false;
do {
    flag[1] = true;
    turn = 0;
    while (flag[0] && turn == 0);
        printf("I am 0 entering in to critical section");
        sleep(3);
        printf("I am 0 exiting from critical section");
    flag[1] = false;
        printf("I am 0 entering in to remainder section");
        sleep(2);    
        printf("I am 0 exiting from remainder section");
} while(true);

}
