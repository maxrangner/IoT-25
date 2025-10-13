# IoT-25:02 - C/C++ Uppgift 1

## Premise
An IoT system often collects sensor readings, for example temperature, moisture levels and pressure. To understand these readings we need to analyze them.

## Assignment
Develop a C/C++ program that process a list of measurements. Your code has to have a GitHub repo, and your work and solution has to be documented in the repo README.


## Features
- `Statistic calculations`
    - Basic statistics: Sum, mean, min, max.
    - Advanced statistics: Variance, standard deviation.
- `Data management`
    - Add values manually.
    - Sort data by value or date.
    - Simulate values by randomizer.
- `Menu system`
    - Menu selection by numbers.
    - Input validation function.


## Usage
1. **Add new values**: Adds new values, one at a time. Input `done` when done. 
2. **Display statistics**: Prints various database statistics to the terminal.
3. **Display graph**: // Work in progress
4. **Display values sorted**: Prints database in order of value or timestamp.
5. **Find value**: Searches for a specific temperature value or timestamp. Input `done` when done.
6. **Simulate values**: Uses random library to fill database with random values.
7. **Quit**: Exits the program with an exit massage.

## Technical Details
- `main()` utilizes a while loop to keep the program running. `menu()` takes user input to select operation, and `action()` triggers coresponding function. `action()` returns `true` when user wants to quit.
- Struct object `DataPoint` to store temperature value and timestamp. Can be expanded with additional data variables in the future.
- Temperature values are stored as `float`. When printed they are limited to two deicmals, calculations are made as `doubles` to increse precition.
- The `DataPoints` are stored in a vector with a limit of five entries, with the oldest entry automatically discarded if needed. The size of the vector is hardcoded with the constant `constexpr int MAX_DATA_POINTS`, and can easily be expanded or connected to an options function in the future.

- Multiple "tool" functions:
    - `getTime()`: Uses the \<ctime> module and returns a tm struct where you can easily extract elements like day or month.
    - `isValidInput`: Validator that takes min and max value, or accepted strings. Constructed as two overload functions, with one handling digitis and one strings.
    - `getRandomTemp` and `getRandomTime`: Returns randomized values utilizing the \<random> module. Temp can be fed optional min and max values. Time requires an int representing the timespan in seconds and returns a valid timestamp between now and x seconds back.

- Main functions:
    - `addValues`: Asks for user input, using `std::getline`. Input is then filtered trough `isValidInput` and paired with a timestamp. If database vector is full, the oldest `DataPoint` is deleted.
    - `printData`: Prints the database vector. Has overloaded version that also prints the stats returned by the `calcStats` function as a struct.
    - `calcStats`: Calculates various statistics and returned as a struct.
    - `findData`: Searches the database vector for input provided by user, and validated with the `isTemperatureValue` or `isData` functions.
    - `sortData`: User can select to sort and display the database vector by either temperature value or timestamp. Saves the sorted data as a temporary vector that is fed to the `printData` function.
    - `generateData`: Returns a `DataPoint` with randomized temperature and timestamp.

## Example output
```
test
```

## History
- 2025/10/13: Finished README.
- 2025/10/11: Finsihed two "VG" functions.
- 2025/10/09: Finished all "G" functions.
- 2025/10/03: Project created.