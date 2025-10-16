#include <stdio.h>
#include <stdlib.h>

// this program accepts command line arguments and displays them
int main(int argc, char *argv[]) {
    int total = 0;
    int tmp;
    for (int i = 0; i < argc; i++) {
        tmp = atoi(argv[i]);
        total += tmp;
    }

    double average = total / (argc -1);

    printf("Average: %.2f\n", average);
}