#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

int balance = 0;

void withdraw() {
    if (balance >= 50){
        balance = balance - 50;
        printf("Withdrawn 50, new balance: %d\n", balance);
    } else {
        printf("Insufficient funds for withdrawal. Current balance: %d\n", balance);
    }
}

int main(void){
    pthread_t threads[NUM_THREADS];

    // Initialize balance
    balance = 100;

    // Create threads to perform withdrawal
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, (void *)withdraw, NULL) != 0) {
            fprintf(stderr, "Failed to create a thread!\n");
        }
    }

    // Wait for all threads to finish
    for (int j = 0; j < NUM_THREADS; j++) {
        pthread_join(threads[j], NULL);
    }

    printf("Final balance: %d\n", balance);
    return 0;
}