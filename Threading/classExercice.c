#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *file[];
    unsigned int lineAmt;
} threadIO;

void *lineCounter(void *ptr){
    threadIO* io = (threadIO*) ptr;
    
    FILE *file;
    char filename[] = io->file; // Replace with your filename
    char ch;
    int lines = 0;

    // 1. Open the file in read mode
    file = fopen(filename, "r");

    // 2. Check if file exists
    if (file == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    // 3. Read character by character until End Of File (EOF)
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    // 4. Close the file
    fclose(file);
    int* ptr_i = (int*)malloc(sizeof(int));
	*ptr_i = lines;
	return (void*)ptr_i;

}

int main(int argc, char *argv[]){
    pthread_t threads[argc - 1];
    int results[argc - 1];

    for(int i = 1; i < argc; i++){
        threadIO* info = malloc(sizeof(threadIO));
        strcpy(threadIO->file, argv[i])
	    pthread_create(threads[i-1], NULL, lineCounter, info);
    }

    for(int i =0; i < (argc-1); i++){
        pthread_join(threads[i], (void**) &results[i])
    }

    for(int i =0; i < (argc-1); i++){
        printf("%d: %d lines", i, results[i])
    }
}