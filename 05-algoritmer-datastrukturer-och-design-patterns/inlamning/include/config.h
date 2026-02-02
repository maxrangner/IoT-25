#ifndef CONFIG_H
#define CONFIG_H

#define QUEUE_CAPACITY 20
#define SET_CAPACITY 10
#define INPUT_CHAR_LIMIT 50
#define TEMP_ALARM_THREASHOLD 25
#define HUMID_ALARM_THREASHOLD 70
#define LUM_ALARM_THREASHOLD 7000

typedef enum DebugLevel {
    NONE,
    INFO,
    ERROR,
    DEBUG
} DebugLevel;


#endif