#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 1. DEFINE YOUR STRUCT
// It needs to hold the integer candidate
typedef struct inOutHandler{
    int input;
    int output;
} threadPacket;


// 2. WRITE YOUR THREAD FUNCTION
// Name: check_prime
// Input: void* (your struct)
// Output: void* (pointer to int: 1 or 0)
// Logic:
//    - If n < 2, not prime.
//    - Loop from i=2 up to i < n.
//    - If n % i == 0, it is NOT prime.
//    - Otherwise, it is prime.
//    - Don't forget to free the input struct!
void* check_prime(void* ptr){
    threadPacket* packet = (threadPacket*) ptr;

    packet->output = 0;
    for(int i = 2; i<packet->input; i++)
    {
        if ((packet->input % i) == 0)
        {
            packet->output = 1;
            break;
        }
    }

    return (void*) packet;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ...\n", argv[0]);
        return 1;
    }

    int num_args = argc - 1;

    // 3. DEFINE ARRAYS
    pthread_t threads[num_args];
    threadPacket results[num_args];
    
    
    // --- CREATION LOOP ---
    for (int i = 0; i < num_args; i++) {
        int num = atoi(argv[i+1]);
        
        // TODO: Malloc struct, fill it, create thread
        // REMEMBER: pthread_create needs the ADDRESS of the thread array slot
        threadPacket* packet = (threadPacket*)malloc(sizeof(threadPacket));
        packet->input = num;
        if(pthread_create(&threads[i], NULL, check_prime, packet) != 0){
            perror("Failed to create thread");
        }
    }

    printf("Main: Checking numbers...\n");

    // --- JOIN LOOP ---
    for (int i = 0; i < num_args; i++) {
        void* retval;
        
        // TODO: Join thread
        // REMEMBER: pthread_join needs the ADDRESS of retval
        pthread_join(threads[i], &retval);        
        
        // TODO: Cast retval to int*, check if NULL, print result, free result
        threadPacket* retPack = (threadPacket*)retval;
        if(retPack->output == 0){
            printf("%d is prime", retPack->input);
        } else {
            printf("%d is not prime", retPack->input);
        }
        printf("\n");
        free(retPack);
    }

    return 0;
}