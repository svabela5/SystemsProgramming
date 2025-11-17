#include <stdio.h>

void crash_here() {
    int *ptr = NULL;   // Pointer with no valid address
    printf("About to crash...\n");
    *ptr = 42;         // Intentional crash: dereferencing NULL
}

void greet() {
    printf("Hello! This program will crash on purpose.\n");
}

int main() {
    greet();
    crash_here();  // Call the crashing function
    printf("You will never see this message.\n");
    return 0;
}
