# IoT-25:03 - OOP och Design Uppgift 2
https://github.com/maxrangner/IoT-25/tree/main/03-OOP-och-Design/IoT-25-OOP-Uppgift2

## Premise
A sensor hub with various types of sensor types. 

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
- `Logger class`
    - Stores a vector of `Measurement` objects.
    - `addMeasurement()` to add new sensor reading to log vector.
    - `getGraphData` creates an array of the 10 last `Measurement` readings, to be used to draw graph in the status screen.
- `InputHandler class`
    - Handles various inputs from the user.
- `Display`
    - Prints varoius messages and draws the status graph.

## Usage
Add / remove sensor and view current data stream with the status screen.

## EXAMPLE OUTPUT

```cpp
*--- StatusScreen ---*

****** Active sensors ******
0: temperature sensor:    23.4C | 1: humidity sensor:       56.7% | 3: temperature sensor:    19.1C
4: temperature sensor:    19.8C | 5: temperature sensor:    25.7C | 6: temperature sensor:    27.7C
7: temperature sensor:    26.1C |
C   ***** temperature sensor: 0 *****
30 | ---------------------------------------------------------------------------
29 | ---------------------------------------------------------------------------
28 | ---------------------------------------------------------------------------
27 | ---------------------------------------------------------------------------
26 | ---------------- x ----- x --------------------- x ------------------------
25 | ----------------   -----   ----- x -------------   ------------- x --------
24 | ----------------   -----   -----   ----- x -----   -------------   --------
23 | -------- x -----   -----   -----   -----   -----   -------------   ----- x
22 | --------   -----   -----   -----   -----   -----   -------------   -----
21 | --------   -----   -----   -----   -----   -----   -------------   -----
20 | --------   -----   -----   -----   -----   -----   -------------   -----
19 | --------   -----   -----   -----   -----   -----   ----- x -----   -----
18 | --------   -----   -----   -----   -----   -----   -----   -----   -----
17 |  x -----   -----   -----   -----   -----   -----   -----   -----   -----
16 |    -----   -----   -----   -----   -----   -----   -----   -----   -----
    13:09 | 13:09 | 13:09 | 13:09 | 13:09 | 13:09 | 13:10 | 13:10 | 13:10 | 14:18

*--- Temperature ---* Average: 23.17 |   Min: 17.09 |   Max: 27.83 |   Variance: 10.91 |   Std dev: 3.30
*----- Humidity ----* Average: 52.79 |   Min: 47.18 |   Max: 57.4 |   Variance: 9.05 |   Std dev: 3.01
*--- Alarm is on ---* temperature: 18 - 26  |  humidity: 48 - 56

> Enter [num] sensorId.
> [enter] to go back.

 >
```

## RUN
Compile with:

` g++ -Iinclude -Isrc src/*.cpp *.cpp -o build/build.exe -std=c++17 -Wall -Wextra -g`