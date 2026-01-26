#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Fixed struct definition
typedef struct {
    char *filename; // Changed from char *file[] to char *filename
} threadIO;

void *lineCounter(void *ptr){
    threadIO* io = (threadIO*) ptr;
    
    // 2. Assign pointer, don't copy arrays incorrectly
    char *filename = io->filename; 
    char ch;
    int lines = 0;

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        free(io); // Free input struct before error return
        return NULL;
    }

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);
    
    // 3. Clean up the argument memory passed from main
    free(io); 

    // 4. Allocate memory for the result (integer)
    int* result = (int*)malloc(sizeof(int));
    *result = lines;
    
    return (void*)result; 
}

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    int num_files = argc - 1;
    pthread_t threads[num_files];
    int results[num_files];

    // --- Creation Loop ---
    for(int i = 0; i < num_files; i++){
        threadIO* info = malloc(sizeof(threadIO));
        
        // 5. Point directly to argv string (no need to strcpy)
        info->filename = argv[i + 1]; 

        // 6. Pass the ADDRESS of the thread identifier (&threads[i])
        if (pthread_create(&threads[i], NULL, lineCounter, info) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // --- Join Loop ---
    for(int i = 0; i < num_files; i++){
        void *retval;

        // 7. Join expects a void** to catch the return value
        if (pthread_join(threads[i], &retval) != 0) {
            perror("Failed to join thread");
            return 2;
        }
        
        // 8. Cast the void* back to int*, dereference, and free
        int *ptr_result = (int*)retval;
        if (ptr_result != NULL) {
            results[i] = *ptr_result;
            free(ptr_result); // Free the memory allocated inside the thread
        } else {
            results[i] = -1; // Error code if thread returned NULL
        }
    }

    // --- Print Loop ---
    for(int i = 0; i < num_files; i++){
        printf("File: %s | Lines: %d\n", argv[i+1], results[i]);
    }
    
    return 0;
}