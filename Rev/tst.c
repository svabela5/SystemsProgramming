#include <stdio.h> 
#include <string.h> 
typedef union U { 
   char name[75]; 
   char surname[75]; 
} u; 
int main() { 
    u test;  
    strcpy(test.name, "Alicia");  
    strcpy(test.surname, "Keys");  
    printf("%s %s is a singer\n", test.name, test.name); 
} 