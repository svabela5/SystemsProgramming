#include <pthread.h>
#include <stdio.h>

// SHARED GLOBAL VARIABLE
int counter = 0; 
pthread_mutex_t mutex;

void* count_up(void* arg) {
    for (int i = 0; i < 500000; i++) {
        // The Race Condition happens here:
        pthread_mutex_lock(&mutex);
        counter++; 
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);

    // Create 2 threads running the same function
    pthread_create(&t1, NULL, count_up, NULL);
    pthread_create(&t2, NULL, count_up, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("Expected: 1000000\n");
    printf("Actual:   %d\n", counter);
    return 0;
}