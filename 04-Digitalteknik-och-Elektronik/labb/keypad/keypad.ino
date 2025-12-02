/*
COMMENT OUT ONE OF THE MODELS (A or B) BEFORE COMPILING!
*/

constexpr uint8_t COLUMNS = 2;
constexpr uint8_t ROWS = 2;
constexpr uint8_t pinColumn1 = 10;
constexpr uint8_t pinColumn2 = 9;
constexpr uint8_t pinRow1 = 21;
constexpr uint8_t pinRow2 = 20;
const int columnPins[COLUMNS] = {pinColumn1, pinColumn2};
const int rowPins[ROWS] = {pinRow1,pinRow2};
const int keypad[ROWS][COLUMNS] = {{1, 2}, {3, 4}};

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
  Serial.println("BOOT!");
}

/*
All pins INPUT_PULLUP == HIGH.
Loop through COLUMNS and switch one by one to OUTPUT LOW.
If a row turns LOW as well we can pinpoint button.
*/
void loop() {
  bool keyFound = false; 
  for (int c = 0; c < COLUMNS; c++) {
    pinMode(columnPins[c], OUTPUT);
    digitalWrite(columnPins[c], LOW);
    for (int r = 0; r < ROWS; r++) {
      if (digitalRead(rowPins[r]) == LOW) {
        Serial.println(keypad[r][c]);
        keyFound = true;
        break;
      }
    }
    pinMode(columnPins[c], INPUT_PULLUP);
    if (keyFound) break;
  }
  delay(10);
}

// MODELL B
void setup() {
  Serial.begin(9600);
  delay(100);
  for (auto& c : columnPins) {
    pinMode(c, INPUT_PULLUP);
  }
  for (auto& r : rowPins) {
    pinMode(r, OUTPUT);
    digitalWrite(r, LOW);
  }
  Serial.println("BOOT!");
}

/*
COLUMNS == INPUT_PULLUP
ROWS = OUTPUT
Loop through COLUMNS and look for one with OUTPUT LOW.
Then turn one row after another HIGH and look for which one turns LOW column back HIGH.
*/
void loop() {
  bool keyFound = false;
  for (int c = 0; c < COLUMNS; c++) {
    if (digitalRead(columnPins[c]) != LOW) continue;
    for (int r = 0; r < ROWS; r++) {
      digitalWrite(rowPins[r], HIGH);
      if (digitalRead(columnPins[c]) == HIGH) {
        Serial.println(keypad[r][c]);
        keyFound = true;
      }
      digitalWrite(rowPins[r], LOW);
      if (keyFound) break;
    }
    if (keyFound) break;
  }
}
