
#include "globals.c"
#include<stdbool.h>
#include<stdio.h>
int main() {
flag[0] = false;
flag[1] = false;
do {
    flag[0] = true;
    turn = 1;
    while (flag[1] && turn == 1);
        printf("I am 1 entering in to critical section");
        sleep(2);
        printf("I am 1 exiting from critical section");
    flag[0] = false;
        printf("I am 1 entering in to remainder section");
        sleep(3); 
        printf("I am 1 exiting from remainder section");
} while(true);

}
