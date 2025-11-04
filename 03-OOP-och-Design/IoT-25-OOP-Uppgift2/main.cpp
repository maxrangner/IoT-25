#include <iostream>
#include "SystemManager.h"
#include "Sensor.h"
#include "SensorHub.h"
#include "TemperatureSensor.h"
#include "Measurement.h"
#include "UiManager.h"
#include "Display.h"
#include "utils.h"

int main() {
    SystemManager sysMan;
    sysMan.run();
  
    return 0;   
} 
