#include "observer.h"
#include "Set.h"

static void logger(Context* ctx, Event event) {
    logAppend(ctx->log, event);
}

static void alarm(Context* ctx, Event event) {
    if (event.sensorType == 0 && event.value >= TEMP_ALARM_THREASHOLD ||
        event.sensorType == 1 && event.value >= HUMID_ALARM_THREASHOLD ||
        event.sensorType == 2 && event.value >= LUM_ALARM_THREASHOLD
    ) {
        setAdd(ctx->set, event.sensorId); // If triggered this tick - put into set
    } else if (event.sensorType == 0 && event.value < TEMP_ALARM_THREASHOLD ||
        event.sensorType == 1 && event.value < HUMID_ALARM_THREASHOLD ||
        event.sensorType == 2 && event.value < LUM_ALARM_THREASHOLD
    ) {
        setRemove(ctx->set, event.sensorId); // If not triggered this tick, remove from set
    }
}

static Observer observers[2] = { alarm, logger };

void notify(Context* ctx, Event event) {
    for (int i = 0; i < sizeof(observers) / sizeof(observers[0]); i++) {
        observers[i](ctx, event);
    }
}
