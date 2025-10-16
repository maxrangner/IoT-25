# IoT-25:02 - C/C++ Uppgift 1
https://github.com/maxrangner/IoT-25/tree/main/02-Programmering-C-och-Cpp/IoT-25-CPP-Uppgift1

## Premise
An IoT system often collects sensor readings, for example temperature, moisture levels and pressure. To understand these readings we need to analyze them.

## Assignment
Develop a C/C++ program that process a list of measurements. Your code has to have a GitHub repo, and your work and solution has to be documented in the repo README.


## Features
I've simulated a temperature sensor that can save, generate, process and display data.
- `Statistic calculations`
    - Basic statistics: Sum, mean, min, max.
    - Advanced statistics: Variance, standard deviation.
- `Data management`
    - Add values manually.
    - Sort data by value or date.
    - Simulate values with a randomizer. Single entry or fill vector.
- `Menu system`
    - Menu selection by numbers.
    - Input validation functions.


## Usage
1. **Add new values**: Adds new values, one at a time. Input `done` when done.
2. **Display current data**: Displays current values in thge database vector.
3. **Display statistics**: Prints various database statistics to the terminal.
4. **Display graph**: // Work in progress
5. **Display values sorted**: Prints database in order of temperature value or timestamp.
6. **Find value**: Searches for a specific temperature value or timestamp. Input `done` when done.
7. **Simulate values**: Uses random library to add a single random value or fill database with random values.
8. **Quit**: Exits the program with an exit massage.

## Technical Details
- `main()` utilizes a while loop to keep the program running. `menu()` takes user input to select operation, and `action()` triggers coresponding function. `action()` returns `true` when user wants to quit.
- Struct object `DataPoint` to store temperature value (`float`) and timestamp (`struct tm`). The choice of a struct is to keep different related data together, and can easily be expanded with additional data variables in the future.
- Temperature values are stored as `float`. When printed they are limited to two decimals, calculations are made as `doubles` to increse precition.
- The `DataPoints` are stored in a `vector` with a limit of five entries, with the oldest entry automatically discarded if needed by the `constrainVectorSize` function. A vector was chosen because of it's dynamic size and available methods, like for example `.size()` and `.empty()`. The size of the `vector` is hardcoded with the constant `constexpr int MAX_DATA_POINTS`, and can easily be changed or connected to an options function in the future.

- Data functions:
    - `addValues`: Asks for user input, using `std::getline`. Input is then filtered trough `isValidInput` and paired with a timestamp. If database vector is full, the oldest `DataPoint` is deleted.
    - `generateDataPoints`: Overloaded function that either returns one `DataPoint` with randomized temperature and timestamp, or as many random DataPoints as the additional argument (`int`) is provided.

- Core functions:
    - `calcStats`: Calculates various statistics and returns a struct with the data.
    - `findData`:  Searches the database vector for input provided by user, and validated with the `isTemperatureValue` or `isData` functions.
    - `sortData`: User can select to sort and display the database vector by either temperature value or timestamp. Saves the sorted data as a temporary vector that is fed to the `printData` function.

- Tool functions:
    - `constrainVectorSize`: Keeps vector to the maximum size -1 to alow for new value to be added afterwards. Size is dictated by `MAX_DATA_POINTS`.
    - `getTime()`: Uses the \<ctime> module and returns a `tm struct`. This is so you can easily extract elements like day or month from built in methods.
    - `getRandomTemp` and `getRandomTime`: Returns randomized values utilizing the \<random> module. Temp can be fed optional min and max values. Time requires an int representing the timespan in seconds and returns a valid timestamp between now and x seconds back.

- Validators:
    - `isTemperatureValue`: Checks if user input is a valid `float`.
    - `isDate`: Checks if user input is in the format xxxx/xx/xx.
    - `isValidInput`: Validator that takes min and max value, or accepted strings. Constructed as two overload functions, with one handling digitis (takes two floats as parameters) and one strings (takes a vector of strings as parameter).

- UI functions:
    - `UIxxx`: Various UI functions that takes user input, calls relevant data or core functions, and prints resulting data.
    - `printData`: Prints the database vector. Has overloaded version that also prints the stats returned by the `calcStats` function as a struct.

## Example output
```
*********** MENU ***********
1. Add new values
2. Display current data
3. Display statistics
4. Display graph
5. Display values sorted
6. Find value
7. Simulate values
8. Quit
> 1
Add new value. If finished, type "done":
> 25.5
> 21.78
> done

*********************************************
*********** CURRENT VECTOR DATA *************
*********************************************

#1: 25.50 - Tue14 Oct 10:49:42
#2: 21.78 - Tue14 Oct 10:49:52
```

## Example build
```
g++ main.cpp src/*.cpp -I src -o build.exe
```

## History
- 2025/10/16: Added comments to code.
- 2025/10/16: Update README.
- 2025/10/16: Refactor project stucture to be more inline with procedural programming.
- 2025/10/15: Updated README.
- 2025/10/13: Updated README.
- 2025/10/11: Finsihed two "VG" functions.
- 2025/10/09: Finished all "G" functions.
- 2025/10/03: Project created.