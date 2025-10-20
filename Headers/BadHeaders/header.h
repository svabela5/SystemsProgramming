//Filegaurd makes sure that the header is only included once
//you can instead use #pragma once at the top of the header file
#ifndef HEADER_H_INCLUDED
    #define HEADER_H_INCLUDED
    #include <stdio.h>
    void test(void) {
        printf("Hello World\n");
    }
#endif