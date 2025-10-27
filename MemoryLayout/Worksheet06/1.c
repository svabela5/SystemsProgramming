#include <stdio.h> 
 
void recurse(int level) { 
    char arry[1024]; 
    printf("%d\n", level); 
    recurse(level + 1); 
} 
 
int main(void) { 
    recurse(1); 
    return 0; 
} 

// To see the stack size on windows use objdump -x <executable>.exe
// To modify the stack size on windows use gcc "-Wl,--stack,4194304" 1.c -o expandedStack.exe