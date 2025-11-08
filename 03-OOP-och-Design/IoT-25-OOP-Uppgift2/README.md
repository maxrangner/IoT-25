# IoT-25:03 - OOP och Design Uppgift 2
https://github.com/maxrangner/IoT-25/tree/main/03-OOP-och-Design/IoT-25-OOP-Uppgift2

*** WORK IN PROGRESS ***

For code more in line with OOP och Design Uppgift 1, please see:
https://github.com/maxrangner/IoT-25/tree/main/02-Programmering-C-och-Cpp/IoT-25-CPP-Uppgift2

## Premise

## Assignment
- Handle multiply sensors of different types.
- Simulate sensor readings from every type.
- Store measurements in a structured way.
- Offer analytics per sensor.
- Read / write sensor data to file.
- Menu UI.
- Clear class separation and file structure.

## Features
This system has a central `SystemManager` class that handles various `Sensors`. Current types are temperature and humidity, but this is easily expandable with more sensor types. 

- `SystemManager class`
    - Owns the different controlling sub-systems.
    - Calls the Ui.run which is the programs main loop.
    - Runs the thread that updates the sensors in the background.
- `SensorHub class`
    - Adds / removes sensors.
    - Updates sensor readings.
- `Ui class`
    - `run()` main program loop which prints the menu and calls `getMenuSelection()` function to access user functions via `menuAction()`.
- `Sensor class` base class
    - `Temperature Sensor` and `Humidity Sensor` inherits from the Sensor base class. 

## RUN
Compile with:

` g++ -Iinclude -Isrc src/*.cpp *.cpp -o build/build.exe -std=c++17 -Wall -Wextra -g`