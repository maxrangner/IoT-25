/*
COMMENT OUT ONE OF THE MODELS (A or B) BEFORE COMPILING!
*/

constexpr uint8_t COLUMNS = 2;
constexpr uint8_t ROWS = 2;
constexpr uint8_t PIN_COL_1 = 10;
constexpr uint8_t PIN_COL_2 = 9;
constexpr uint8_t PIN_ROW_1 = 21;
constexpr uint8_t PIN_ROW_2 = 20;
const int columnPins[COLUMNS] = {PIN_COL_1, PIN_COL_2};
const int rowPins[ROWS] = {PIN_ROW_1,PIN_ROW_2};
const int keypadValues[ROWS][COLUMNS] = {{1, 2}, {3, 4}};
bool keypadStates[ROWS][COLUMNS];
bool keypadStatesPrev[ROWS][COLUMNS];
String buttonPressed = "0";

uint16_t buzzerVal = 10;
unsigned long now = micros();
unsigned long nextBuzz = 0;

uint8_t pinBuzzer = 0;

// MODELL A
void setup() {
  Serial.begin(9600);
  delay(100);
  for (auto& c : columnPins) {
    pinMode(c, INPUT_PULLUP);
  }
  for (auto& r : rowPins) {
    pinMode(r, INPUT_PULLUP);
  }

  for (int c = 0; c < COLUMNS; c++) {
    for (int r = 0; r < ROWS; r++) {
      keypadStates[r][c] = false;
    }
  }
  pinMode(pinBuzzer, OUTPUT);
  Serial.println("BOOT!");
}

/*
All pins INPUT_PULLUP == HIGH.
Loop through COLUMNS and switch one by one to OUTPUT LOW.
If a row turns LOW as well we can pinpoint button.
*/
void loop() {
  checkMatrix();
  if (keypadStates != keypadStatesPrev) {
    Serial.println(buttonPressed);
  }
  for (int c = 0; c < COLUMNS; c++) {
    for (int r = 0; r < ROWS; r++) {
      keypadStatesPrev[r][c] = keypadStates[r][c];
    }
  }
}

void checkMatrix() {
  for (int c = 0; c < COLUMNS; c++) {
    pinMode(columnPins[c], OUTPUT);
    digitalWrite(columnPins[c], LOW);
    for (int r = 0; r < ROWS; r++) {
      if (digitalRead(rowPins[r]) == LOW) {
        keypadStates[r][c] = true;
        buttonPressed = keypadValues[r][c];
      } else keypadStates[r][c] = false;
    }
    pinMode(columnPins[c], INPUT_PULLUP);
  }
}

// void buzz(uint16_t buzzerVal) {
//   now = micros();
//   nextBuzz = 
  
// }

// // MODELL B
// void setup() {
//   Serial.begin(9600);
//   delay(100);
//   for (auto& c : columnPins) {
//     pinMode(c, INPUT_PULLUP);
//   }
//   for (auto& r : rowPins) {
//     pinMode(r, OUTPUT);
//     digitalWrite(r, LOW);
//   }

//   for (int c = 0; c < COLUMNS; c++) {
//     for (int r = 0; r < ROWS; r++) {
//       keypadStates[r][c] = false;
//     }
//   }

//   Serial.println("BOOT!");
// }

// /*
// COLUMNS == INPUT_PULLUP
// ROWS = OUTPUT
// Loop through COLUMNS and look for one with OUTPUT LOW.
// Then turn one row after another HIGH and look for which one turns LOW column back HIGH.
// */
// void loop() {
//   bool keyFound = false;
//   for (int c = 0; c < COLUMNS; c++) {
//     if (digitalRead(columnPins[c]) != LOW) continue;
//     for (int r = 0; r < ROWS; r++) {
//       digitalWrite(rowPins[r], HIGH);
//       if (digitalRead(columnPins[c]) == HIGH) {
//         Serial.println(keypad[r][c]);
//         keyFound = true;
//       }
//       digitalWrite(rowPins[r], LOW);
//       if (keyFound) break;
//     }
//     if (keyFound) break;
//   }
// }
