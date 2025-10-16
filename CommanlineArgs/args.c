#include <stdio.h>

// this program accepts command line arguments and displays them
int main(int argc, char *argv[]) {
    printf("Program: ");
    printf("Number of arguments: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
}