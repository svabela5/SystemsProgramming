#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h> // Needed for malloc/free
#include <unistd.h> // Needed for sleep()


#define NAME_SIZE 32

pthread_mutex_t mutex;
char* outfile;

typedef struct {
    char name[NAME_SIZE];
    unsigned int delay;
    unsigned int maximum;
} thread_info;

void* DoWork(void* ptr){
    thread_info* payload = (thread_info*) ptr;

    
    for(int i = 0; i < payload->maximum; i++){
        pthread_mutex_lock(&mutex);
        FILE* fp = fopen(outfile, "a");
        if(fp){
            fprintf(fp, "%s\n", payload->name);
            fclose(fp);
        } else {
            printf("Error Opening AFile");
        }
        pthread_mutex_unlock(&mutex);

        sleep(payload->delay);
    }
}

int main(int argc, char *argv[]){

    if (argc < 3)
    {
        /* code */
        printf("More Args Required");
        return 1;
    }
    
    pthread_mutex_init(&mutex, NULL);
    outfile = argv[1];
    char input[NAME_SIZE];

    FILE* inputFP = fopen(argv[2], "r");
    int count;
    fscanf(inputFP, "%d", &count);
    printf("%d", count);
    pthread_t threads[count];
    for(int i = 0; i < count; i++){
        thread_info* info = (thread_info*) malloc(sizeof(thread_info));

        fscanf(inputFP, "%s %d %d", info->name, &(info->delay), &(info->maximum));
        
		printf("read %s,%d,%d\n", info->name, info->delay, info->maximum);
        pthread_create(&threads[i], NULL, DoWork, info);
    }

    for (int i = 0; i < count; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    

    // while(strcmp(input, "quit")){
    //     pthread_t thread;
    //     thread_info* info = (thread_info*) malloc(sizeof(thread_info));

    //     printf("Enter a name: ");
    //     if (scanf("%s", input)){
    //         if(strcmp(input, "quit") == 0){
    //             return 0;
    //         }
    //         strcpy(info->name, input);
    //     }
    //     printf("Enter de delay: ");
    //     scanf("%d", &(info->delay));
    //     printf("Enter maximum: ");
    //     scanf("%d", &(info->maximum));

    //     pthread_create(&thread, NULL, DoWork, info);
    // }
}