#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

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

struct Message printMessage(struct Message msg)
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

struct Message newMessge(void){
    int choice;
    struct Message newMsg;

    printf("Press 1 to enter error code\n");
    printf("Press 2 to enter temperature\n");
    printf("Press 3 to enter text message\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            newMsg.type = ERROR;
            printf("Enter error code (integer): ");
            scanf("%d", &newMsg.data.errorCode);
            break;
        case 2:
            newMsg.type = TEMPERATURE;
            printf("Enter temperature (float): ");
            scanf("%f", &newMsg.data.temperature);
            break;
        case 3:
            newMsg.type = TEXT;
            printf("Enter text message: ");
            getchar();
            scanf("%49[^\n]", &newMsg.data.text);
            break;
        default:
            break;
    }
    return newMsg;
}

void printMenu(void){
        printf("\nMenu:\n");
        printf("1) Add\n");
        printf("2) Remove\n");
        printf("3) Show at index\n");
        printf("4) Show all\n");
        printf("5) Exit\n");
        printf("Enter your choice: \n");
}

int main(void)
{
    struct Message Messages[MAX];
    int count = 0;
    int choice = 0;

    while (choice != 5)
    {
        printMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (count < MAX)
            {
                Messages[count] = newMessge();
                count++;
            }else{
                printf("Array is full");
            }
            break;
        case 2:
            count --;
            // Messages[count] = NULL;
            break;
        case 3:
            printf("Select index to show");
            scanf("%d", &choice);
            if (choice > 0 && choice < count)
            {
                printMessage(Messages[choice]);
            } else {
                printf("invalid index");
            }
            break;
        case 4:
            for (int i = 0; i < count; i++)
            {
                printMessage(Messages[i]);
            }
            break;
        default:
            break;
        }
    }
    
    printf("Goodbye");
}