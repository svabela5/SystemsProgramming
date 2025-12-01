#include <stdio.h>
#include <string.h>

enum MessageType { ERROR, TEMPERATURE, TEXT };

union MessageData {
        int errorCode;
        float temperature;
        char text[50];
    };

struct Message {
        enum MessageType type;
        union MessageData data;
    };


struct Message fillErrorMessage(int error){
    struct Message msg;
    msg.type = ERROR;
    msg.data.errorCode = error;
    return msg;
}

struct Message fillTemperatureMessage(float Temp){
    struct Message msg;
    msg.type = TEMPERATURE;
    msg.data.temperature = Temp;
    return msg;
}

struct Message fillTextMessage(char text[50]){
    struct Message msg;
    msg.type = TEXT;
    strcpy(msg.data.text, text);
    return msg;
}