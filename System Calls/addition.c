#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>

int main() {
    int num1 = 10;
    int num2 = 20;
    printf("I am child transformed into additon program\n");
    printf("Sum of num1=%d and num2=%d is %d \n",num1,num2,num1+num2);
    exit(10);
}