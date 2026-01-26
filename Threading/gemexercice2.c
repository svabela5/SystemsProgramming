#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Useful for tolower() if you want
#include <unistd.h> // For sleep()

// 1. DEFINE YOUR STRUCT HERE
// It needs to hold the word (char*)
typedef struct {
    char* word;
} Payload;


// 2. WRITE YOUR THREAD FUNCTION HERE
// Name: count_vowels
// Input: void* (your struct)
// Output: void* (pointer to int)
// Logic: Loop through string, count vowels, sleep(1) for realism, return result.
void* vowelCounter(void* ptr){
    Payload* load = (Payload*) ptr;

    sleep(1);
    
    int* vowelCount = (int*)malloc(sizeof(int));
    *vowelCount = 0;

    // Inside your thread function...
    char *word = load->word; // Get the string from your struct

    // Loop until the end of the string ('\0')
    for (int i = 0; word[i] != '\0'; i++) {
        // 1. Convert to lowercase to handle 'A' and 'a' easily
        char c = tolower(word[i]); 

        // 2. Check against vowels
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            (*vowelCount)++;
        }
    }

    free(load);
    return (void*)vowelCount;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <word1> <word2> ...\n", argv[0]);
        return 1;
    }

    int num_args = argc - 1;

    // 3. DEFINE YOUR THREAD ID ARRAY AND RESULT ARRAY
    pthread_t threads[num_args];
    int results[num_args];
    
    
    // --- CREATION LOOP ---
    // Loop through args, malloc struct, fill struct, pthread_create
    for (int i = 0; i < num_args; i++) {
        Payload* load = (Payload*)malloc(sizeof(Payload));
        load->word = argv[i+1];

        pthread_create(&threads[i], NULL, vowelCounter, load);
        
    }

    printf("Main: Threads launched, waiting for results...\n");

    int total_vowels = 0;

    // --- JOIN LOOP ---
    // Loop through threads, pthread_join, print individual result, add to total, free memory
    for (int i = 0; i < num_args; i++) {
        void* retVal;
        pthread_join(threads[i], &retVal);
        results[i] = *((int*) retVal);
        total_vowels = total_vowels + results[i];
        free(retVal);
    }

    printf("Total Vowels found: %d\n", total_vowels);
    return 0;
}