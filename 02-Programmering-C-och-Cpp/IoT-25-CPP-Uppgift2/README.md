# IoT-25:02 - C/C++ Uppgift 2
https://github.com/maxrangner/IoT-25/tree/main/02-Programmering-C-och-Cpp/IoT-25-CPP-Uppgift2

## Premise
An IoT system often collects sensor readings, for example temperature, moisture levels and pressure. To understand these readings we need to analyze them.

## Assignment
Develop a C/C++ program that process a list of measurements. Your code has to have a GitHub repo, and your work and solution has to be documented in the repo README.

## Features
This system has a central `SystemManager` class that handles various `Sensors`. Current types are temperature and humidity, but this is easily expandable with more sensor types. The manager can then collect measured values from a single or all sensors, and stores them in a database for processing like printout, lookup, and statistics.

The code is built upon C/C++ Uppgift 1, but utilizing classes instead of a procedural approach.

- `SystemManager class`
    - Add / remove sensor.
    - Collect readings.
    - Process data for:
        - Statistics.
        - Lookup.
        - Save / load system state. This feature restores all sensors from the last reading.
- `Ui class`
    - `menu()` function to access user functions.
    - Handles input validation.
    - Displays requested data.
- `Sensor class`
    - Data handled:
        - `deviceId`: Unique number for every sensor added.
        - `type`: Temperature or humidity
        - `value`: Float.
        - `isActive`: Toggle on / off (not yet implemented)
        - `isTriggered`: Trigger flag for motion sensors etc. (not yet implemented)


## Usage
1. **Add Sensor**: Adds new sensor to SystemManager.
2. **Remove Sensor**: Removes sensor from SystemManager.
3. **Collect Readings**: Takes readings from all sensor currently in SystemManager. This is stored in a container for later access.
4. **Display Collected Readings**: Prints out all stored Sensor snapshots, sorted by date.
5. **Sort Collected Readings**: Prints out all stored Sensor snapshots, sorted by value.
6. **Find Collected Readings**: Search by date (xxxx/xx/xx) or value.
7. **Disp Statistics**: Prints out statistics from all Sensor snapshots, sorted by sensor type.
8. **Save System State**: Saves the state of the SystemManager to file (`data.txt`).
9. **Load System State**: Loads the state of the SystemManager from file (`data.txt`). Restores all sensors from last timestamp in database.
10. **Quit**: Exits the program with an exit massage.


## Technical Details
- `main()` utilizes a while loop to keep the program running. `Ui.menu()` takes user input to select option, and `Ui.menuAction()` triggers coresponding function. The `bool` `Ui.isRunning` exits this loop when set to false.
- Struct `DataPoint` to store sensor id (`int`), type (`int`), value (`float`), isActive (`bool`), isTriggered (`bool`). The choice of a struct is to keep different related data together, and can easily be expanded with additional data variables in the future.
- `Sensor` values are stored as `float`. When printed they are limited to two decimals, calculations are made as `doubles` to increse precition.
- SystemManager object stores a `vector` of currently present `sensor` objects, and a `map` with previously measured sensor states as `DataPoints`.
    - The `map` concists of a key: `time_t` timestamp, and a value: `vector` of `DataPoints`. The map was chosen because it groups the different sensor "snapshots" by a common variable. In this case a `timestamp`. And the value `vector` was chosen because it is dynamically expandable.

## Project structure
- Sensor class:
    - updateReading(): Fetches new reading from `sensor`. Currently connected to a random number generator to simulate values.
    - Some methods to access private variables:
        - `deviceId`
        - `type`
        - `value`
        - `isActive`
        - `isTriggered`
    
- SystemManager class:
    - Handles a `map`(key: `time_t` , value: `vector<DataPoint>`) to store collected `Sensor` readings, easily accessable by timestamp.
    - `sensorsList()` stores a list of all current `Sensor` objects. At load from file, this list is restored from the last timestamp entry.
    - Add / remove `Sensor` objects from the `sensorsList()`.
    - Reads and writes the state of the SystemManager to a file in `.txt` format.
    - Sorts data by value, grouped by `Sensor` type.
    - Find entry in history by either full date, or by value.
    - Calculates statistics based on all entires in database.

- `UiManager class`:
    - Is called by the `main()` function.
    - Triggered by `menu()` method.
    - Can take input and validates it before triggering corsponding data functions. 

- `General functions`:
    - `getRandomNumber()`: Generates a random float value. Restrained if given min / max arguments.
    - Different validators.
    - `readTime()`: Takes a `time_t` and converts to string format: xxxx/xx/xx (year/month/day).
    - `readDate()`: Takes a `time_t` and converts to string format: xxxx/xx/xx (year/month/day).



## Example output
```
***************************************
********** SUPER SENSOR HUB ***********
***************************************


*--- MENU ---*
1.  Add Sensor
2.  Remove Sensor
3.  Collect Readings
4.  Display Collected Readings
5.  Sort Collected Readings
6.  Find Collected Readings
7.  Disp Statistics from Collected Readings
8.  Save System State
9.  Load System State
10. Quit
*-----------*
> 1
Add sensor: [t]emperature or [h]umidity. Leave empty to finish.
> t
>
1 sensors added.

*--- MENU ---*
1.  Add Sensor
2.  Remove Sensor
3.  Collect Readings
4.  Display Collected Readings
5.  Sort Collected Readings
6.  Find Collected Readings
7.  Disp Statistics from Collected Readings
8.  Save System State
9.  Load System State
10. Quit
*-----------*
> 3
Enter deviceId or press "enter" for all.
>

*--- MENU ---*
1.  Add Sensor
2.  Remove Sensor
3.  Collect Readings
4.  Display Collected Readings
5.  Sort Collected Readings
6.  Find Collected Readings
7.  Disp Statistics from Collected Readings
8.  Save System State
9.  Load System State
10. Quit
*-----------*
> 4

*---------------- Fri24 Oct 17:56:37 ----------------*
deviceId: 0 | type: temperatureSensor | value: 22.23 C | isActive: true | isTriggered: false
```

## Example build
```
g++ main.cpp src/*.cpp -I src -I include -o build.exe
```

## History
- 2025/10/24: Added README.