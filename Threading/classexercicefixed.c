#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// 1. Simplified Struct: We only need a pointer to the filename string
typedef struct {
    char *filename; 
} threadIO;

void *lineCounter(void *ptr){
    threadIO* io = (threadIO*) ptr;
    
    // 2. Fix: Assign pointer directly
    char *filename = io->filename; 
    
    FILE *file = fopen(filename, "r");

    // 3. Error Handling: return NULL so main knows something failed
    if (file == NULL) {
        printf("Thread Error: Could not open file %s\n", filename);
        return NULL; 
    }

    int lines = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);

    // 4. Return the result safely
    int* ptr_i = malloc(sizeof(int));
    if (ptr_i == NULL) { perror("Malloc failed"); return NULL; }
    *ptr_i = lines;
    
    // Free the struct we passed in to avoid leaking that memory
    free(io); 
    
    return (void*)ptr_i;
}

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    int numFiles = argc - 1;
    pthread_t threads[numFiles];
    int results[numFiles]; // To store final counts

    // --- CREATE THREADS ---
    for(int i = 0; i < numFiles; i++){
        threadIO* info = malloc(sizeof(threadIO));
        
        // Fix: Just point to the argv string. No copying needed.
        info->filename = argv[i + 1]; 
        
        // Fix: Pass the address of the thread ID (&threads[i])
        if (pthread_create(&threads[i], NULL, lineCounter, info) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // --- JOIN THREADS ---
    for(int i = 0; i < numFiles; i++){
        void *returnValue;
        
        // Fix: Catch the pointer returned by the thread
        pthread_join(threads[i], &returnValue);

        if (returnValue != NULL) {
            // Cast back to int*, dereference to get value, then free
            int *ptr_count = (int*)returnValue;
            results[i] = *ptr_count;
            free(ptr_count); // Vital: Free the memory allocated inside the thread
        } else {
            results[i] = -1; // Mark as error
        }
    }

    // --- PRINT RESULTS ---
    for(int i = 0; i < numFiles; i++){
        if (results[i] != -1) {
            printf("File: %s | Lines: %d\n", argv[i+1], results[i]);
        }
    }
    
    return 0;
}