#ifndef WS08C_H
#define WS08C_H

#include <stdbool.h>
#include <stdio.h>

enum MessageType { ERROR, TEMPERATURE, TEXT} ;

union MessageData {
    int errorCode;
    float temperature;
    char text[50];
    
};
    
struct Message {
    enum MessageType type;
    union MessageData data;
};

typedef struct MsgList{
    struct Message* messagePtr;
    size_t size;
    size_t capacity;
} List;

bool addMessage(List* list, struct Message msg);
bool getErrorCodeMessage(struct Message* msg);
bool getTemperatureMessage(struct Message* msg);
bool getTemperatureMessage(struct Message* msg);
char* getUserInput(const char* prompt);
bool getTextMessage(struct Message* msg);
void freeMsgList(List* list);
void displayTasks(List* list);

#endif