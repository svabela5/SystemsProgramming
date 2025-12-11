#include "messages.h"

int main(void){
    List list = {NULL, 0, 0};

    while(true){
        printf("Message Handler Menu\n");
        printf("1. Enter an error message\n");
        printf("2. Enter a temperature message\n");
        printf("3. Enter a text message\n");
        printf("4. Display all messages\n");
        printf("5. Exit\n");
        printf("Choice: ");
        
        int choice;
        int check = scanf("%d", &choice);
        if(check != 1){
            printf("Input is incorrect.");
            int c;
            while((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }

        int c;
        while((c = getchar()) != '\n' && c != EOF) {}

        switch(choice){
            case 1: {
                struct Message msg;
                if(!getErrorCodeMessage(&msg)){
                    printf("Issue creating error code.\n");
                    continue;
                }
                if (!addMessage(&list, msg)){
                    printf("Could not store error message.\n");
                }
            } break;
            case 2: {
                struct Message msg;
                if(!getTemperatureMessage(&msg)){
                    printf("Issue creating tempreature message.\n");
                    continue;
                }
                if (!addMessage(&list, msg)){
                    printf("Could not store error message.\n");
                }
            } break;
            case 3: {
                struct Message msg;
                if(!getTextMessage(&msg)){
                    printf("Issue creating text message.\n");
                    continue;
                }
                if (!addMessage(&list, msg)){
                    printf("Could not store error message.\n");
                }
            } break;
            case 4: {
                displayTasks(&list);
            } break;
            case 5: {
                printf("Exiting...\n");
                freeMsgList(&list);
                return 0;
            } break;
            default: {
                printf("\nWrong choice. Retry.\n");
                continue;
            }
        }
    }
}