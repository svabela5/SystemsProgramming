#include <stdlib.h>
#include <string.h>
#include "messages.h"

bool addMessage(List* list, struct Message msg){
    if(list->size == list->capacity){
        size_t newCapacity = list->capacity == 0 ? 2 : list->capacity * 2;
        struct Message* temp = realloc(list->messagePtr, newCapacity * sizeof(struct Message));
        if(!temp){ 
            printf("Memory allocation failed.\n");
			return false;
        }
        list->messagePtr = temp;
        list->capacity = newCapacity;
    }

    list->messagePtr[list->size++] = msg;
    return true;
}

bool getErrorCodeMessage(struct Message* msg){
    int code;
    printf("\nEnter error code (integer): ");
    int check = scanf("%d", &code);
    if(check != 1){
        printf("Input is incorrect.\n");
        int c;
        while((c = getchar()) != '\n' && c != EOF) {}
        return false;
    }

    int c;
    while((c = getchar()) != '\n' && c != EOF) {}

    msg->type = ERROR;
    msg->data.errorCode = code;
    return true;
}

bool getTemperatureMessage(struct Message* msg){
    float tempVal;
    printf("\nEnter temperature (float): ");
    int check = scanf("%f", &tempVal);
    if(check != 1){
        printf("Input is incorrect.\n");
        int c;
        while((c = getchar()) != '\n' && c != EOF) {}
        return false;
    }
    
    int c;
    while((c = getchar()) != '\n' && c != EOF) {}

    msg->type = TEMPERATURE;
    msg->data.temperature = tempVal;
    return true;
}

char* getUserInput(const char* prompt){
    char buffer[1000];
    printf("%s", prompt);
    if(!fgets(buffer, sizeof(buffer), stdin)) return NULL;

    if(!strchr(buffer, '\n')){
        printf("\nInput is too long!\n");
        int c;
        while((c = getchar()) != '\n' && c != EOF){}
        return NULL;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if(strlen(buffer) == 0){
        printf("\nInput cannot be empty.\n");
        return NULL;
    }

    char* result = malloc(strlen(buffer) + 1);
    if(!result){
        printf("\nMemory could not be allocated.\n");
        return NULL;
    }

    strcpy(result, buffer);
    return result;
}

bool getTextMessage(struct Message* msg){
    char* text = getUserInput("\nEnter text message: ");
    if(!text){
        printf("Issue with storing your text in memory.\n");
        return false;
    }

    if(strlen(text) + 1 > sizeof(msg->data.text)){
        printf("Input cannot be longer than 49 characters.\n");
        free(text);
        return false;
    }

    msg->type = TEXT;
    strcpy(msg->data.text, text);
    free(text);
    return true;
}

void freeMsgList(List* list){
    free(list->messagePtr);
    list->messagePtr = NULL;
    list->size = 0;
    list-> capacity = 0;
}

void displayTasks(List* list){
    if(list->size == 0){
        printf("No messages entered.\n");
        return;
    }

    printf("\nStored Messages\n");
    for(size_t i = 0; i < list->size; i++){
        switch(list->messagePtr[i].type){
            case ERROR:{
                printf("\n[Error Code] %d", list->messagePtr[i].data.errorCode);
            } break;
            case TEMPERATURE: {
                printf("\n[Temperature] %.2f", list->messagePtr[i].data.temperature);
            } break;
            case TEXT: {
                printf("\n[Text] %s", list->messagePtr[i].data.text);
            }
        }
    }
    printf("\n\n");
}
