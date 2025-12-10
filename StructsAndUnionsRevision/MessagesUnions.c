#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "messages.h"




int main() {
    int choice;
    int i;
    float f;

    struct Message oneMessage;
    //FILL IN
    printf("Press 1 to enter code");
    printf("Press 2 to enter temperature");
    printf("Press 3 to enter text");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            printf("Enter error code: ");
            scanf("%d", &i); //test
            oneMessage = fillErrorMessage(i);
            break;
        case 2:
            oneMessage.type = TEMPERATURE;
            printf("Enter temperature: ");
            scanf("%f", &f); 
            oneMessage = fillTemperatureMessage(f);
            break;
        case 3:
            printf("Enter Error Message: ");
            getchar();
            char* msg = (char*)malloc(50 * sizeof(char));
            scanf("%49[^\n]", msg);  //test because of leading whitespace
            oneMessage = fillTextMessage(msg);
            break;
        default:
            break;
    }
    //DISPLAY
    switch(oneMessage.type){
        case ERROR :
            printf("[ERROR CODE]  %d\n", oneMessage.data.errorCode);
            break;
        case TEMPERATURE:
            printf("[TEMPERATURE] %f\n", oneMessage.data.temperature);
            break;
        case TEXT:
            printf("[ERROR MESSAGE] %s\n", oneMessage.data.text);
            break;
    }
}
    