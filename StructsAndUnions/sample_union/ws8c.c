#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum MessageType {
    ERROR,
    TEMPERATURE,
    TEXT
};

union MessageData {
    int errorCode;
    float temperature;
    char text[50];
};

struct Message {
    enum MessageType type;
    union MessageData data;
};

void printMessage(struct Message msg)
{
    switch (msg.type)
    {
        case ERROR:
            printf("Error Code: %d\n", msg.data.errorCode);
            break;
        case TEMPERATURE:
            printf("Temperature: %.2f\n", msg.data.temperature);
            break;
        case TEXT:
            printf("Text Message: %s\n", msg.data.text);
            break;
        default:
            printf("Unknown message type.\n");
            break;
    }
}

int main(void)
{
    int choice;
    struct Message oneMessage;

    printf("Press 1 to enter error code\n");
    printf("Press 2 to enter temperature\n");
    printf("Press 3 to enter text message\n");
    printf("Press 4 to view the message\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            oneMessage.type = ERROR;
            printf("Enter error code (integer): ");
            scanf("%d", &oneMessage.data.errorCode);
            break;
        case 2:
            oneMessage.type = TEMPERATURE;
            printf("Enter temperature (float): ");
            scanf("%f", &oneMessage.data.temperature);
            break;
        case 3:
            oneMessage.type = TEXT;
            printf("Enter text message: ");
            getchar();
            scanf("%49[^\n]", &oneMessage.data.text);
            break;
        default:
            break;
    }

    printMessage(oneMessage);
}