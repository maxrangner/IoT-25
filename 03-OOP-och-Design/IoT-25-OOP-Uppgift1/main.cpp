#include <iostream>
#include "Sensor.h"
#include "SensorHub.h"
#include "TemperatureSensor.h"
#include "Measurement.h"
#include "UiManager.h"
#include "utils.h"

int main() {
    SensorHub hub;
    UiManager Ui;

    while (true) {
        Ui.menu();
    }
    // hub.addSensor();
    // hub.addSensor();
    // hub.addSensor();
    // hub.addSensor();

    // hub.printAllInfo();

    // hub.removeSensor(2);
    // hub.printAllInfo();
    
    return 0;
} 