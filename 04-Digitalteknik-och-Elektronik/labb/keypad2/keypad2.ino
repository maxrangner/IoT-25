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
String buttonVal = "0";
unsigned long now = 0;
unsigned long buttonPressedMillis = 0;
unsigned long buttonHoldThreashold = 300;

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);

  for (auto& c : columnPins) {
    pinMode(c, INPUT_PULLUP);
  }
  for (auto& r : rowPins) {
    pinMode(r, INPUT_PULLUP);
  }
  memset(keypadStates, 0, sizeof(keypadStates));
  Serial.println("BOOT!");
}

void loop() {
  checkMatrixStates();
  if (keypadStatesHasChanged()) {
    Serial.println(buttonVal);
  }
  setMatrixStatesPrev();
  delay(50);
}

void checkMatrixStates() {
  for (int c = 0; c < COLUMNS; c++) {
    pinMode(columnPins[c], OUTPUT);
    digitalWrite(columnPins[c], LOW);
    for (int r = 0; r < ROWS; r++) {
      if (digitalRead(rowPins[r]) == LOW) {
        keypadStates[r][c] = true;
        buttonVal = keypadValues[r][c];
      } else keypadStates[r][c] = false;
    }
    pinMode(columnPins[c], INPUT_PULLUP);
  }
}

void setMatrixStatesPrev() {
  for (int c = 0; c < COLUMNS; c++) {
    for (int r = 0; r < ROWS; r++) {
      keypadStatesPrev[r][c] = keypadStates[r][c];
    }
  }
}

bool keypadStatesHasChanged() {
  now = millis();
  for (int c = 0; c < COLUMNS; c++) {
    for (int r = 0; r < ROWS; r++) {
      if (keypadStatesPrev[r][c] == false && keypadStates[r][c] == true) {
        buttonPressedMillis = now;
      }
      if (keypadStatesPrev[r][c] == true && keypadStates[r][c] == false && now - buttonPressedMillis >= buttonHoldThreashold) {
        Serial.print("Hold: ");
        return true;
      } else if (keypadStatesPrev[r][c] == true && keypadStates[r][c] == false) {
        Serial.print("Pressed: ");
        return true;
      }
    }
  }
  return false;
}

