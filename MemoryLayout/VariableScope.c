#include <stdio.h>
#include <stdlib.h>
 
int global_init = 10;
int global_uninit;
 
void test(void){
    int local = 20;
    static int local_static = 50;
    printf("Local %d.  Address (STACK) %p\n", local, &local);  //this value dies with the function
    printf("Local Static %d.  Address (DATA) %p\n", local_static, &local_static);
    global_init++;  //Very BAD Programming  :)
    local_static++; /// the new value is incremented, this variable stays alive!!
 
}
 
int main(void){
    printf("Global_int %d. Address (DATA) %p\n", global_init, &global_init);
    printf("Global_uninit%d. Address (BSS) %p\n", global_uninit, &global_uninit);
    // printf("Local %d\n", local);
    // printf("Local Static %d\n", local_static);  //cannot refer outside function
    test();
    int * p = (int*)malloc(sizeof(int));
    printf("The address of the pointer %p (STACK)\n", &p);
    printf("The address of the dynamic block %p (HEAP)\n", p);    
    printf("The stack frame of test is at address (STACK) %p\n", test);
    printf("The stack frame of main is at address (STACK) %p\n", main);
    printf("Global_int %d\n", global_init);
}