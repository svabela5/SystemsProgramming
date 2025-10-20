#include <stdio.h>
// To add defines through gcc we use the -D tag where it needs to be as follows: 
// -DTAG no space between the d and the tag this needs to be done when compiling

int main(void) {
    #ifdef FULL
        printf("Full Demo Enabled\n");
    #else
        printf("This is the demo version\n");
    #endif
}
