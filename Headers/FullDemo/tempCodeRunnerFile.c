#include <stdio.h>

int main(void) {
    #ifdef Full
        printf("Full Demo Enabled\n");
    #else
        printf("THis is the demo version\n");
    #endif
}