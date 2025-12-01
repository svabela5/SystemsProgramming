#ifndef MESSAGES_H
#define MESSAGES_H

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

struct Message fillErrorMessage(int error);

struct Message fillTemperatureMessage(float Temp);

struct Message fillTextMessage(char text[50]);
#endif