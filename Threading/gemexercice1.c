#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep()

// 1. Define the struct to hold the input number
typedef struct {
    int value;
} number_payload;

void *square_calculator(void *ptr) {
    // TODO 1: Cast 'ptr' back to the struct pointer type
    number_payload* payload = (number_payload*) ptr;
    
    // TODO 2: Extract the integer value
    int x = payload->value;
    
    // Simulate complex work
    sleep(1); 
    
    // TODO 3: Calculate the square
    int square = x*x;
    
    // TODO 4: Allocate memory (malloc) for the result (int) and store the calculation
    int* result = (int*)malloc(sizeof(int));
    *result = square;
    
    // TODO 5: Free the input struct (ptr)
    free(payload);
    
    // TODO 6: Return the result pointer
    return (void*)result; // Replace NULL with your result
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ...\n", argv[0]);
        return 1;
    }

    int count = argc - 1;
    pthread_t threads[count];
    int final_results[count];

    // --- CREATION LOOP ---
    for (int i = 0; i < count; i++) {
        int current_num = atoi(argv[i + 1]); // Converts string "5" to int 5

        // TODO 7: Malloc a new number_payload struct
        number_payload* payload = (number_payload*)malloc(sizeof(number_payload));

        // TODO 8: Assign 'current_num' into the struct
        payload->value = current_num;

        // TODO 9: Create the thread, passing the struct as the argument
        if (pthread_create(&threads[i], NULL, square_calculator, payload) != 0) {
            perror("Failed to create thread");
        }
    }

    printf("Main thread: Waiting for results...\n");

    // --- JOIN LOOP ---
    for (int i = 0; i < count; i++) {
        void *retval;

        // TODO 10: Join the thread and capture the return value in 'retval'
        if (pthread_join(threads[i], &retval) != 0)
        {
            perror("Failed to join thread");
            return 2;
        }
        
        
        // TODO 11: Cast retval to int*, dereference it to get the value, and store in final_results[i]
        int* result = (int*)retval;
        final_results[i] = *result;

        // TODO 12: Free the memory allocated inside the thread
        free(result);
    }

    // Print results
    for (int i = 0; i < count; i++) {
        printf("Input: %s | Square: %d\n", argv[i+1], final_results[i]);
    }

    return 0;
}