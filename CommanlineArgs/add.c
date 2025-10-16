#include <stdio.h>
#include <stdlib.h>

//write a program that accepts two numbers at command line and displays the addition
//of these numbers

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("You need to enter 2 numbers-+");
        return 1;
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    printf("Sum: %d\n", num1 + num2);
    return 0;
}