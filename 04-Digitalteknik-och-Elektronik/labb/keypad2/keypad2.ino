constexpr uint8_t COLUMNS = 2;
constexpr uint8_t ROWS = 2;
constexpr uint8_t PIN_COL_1 = 10;
constexpr uint8_t PIN_COL_2 = 9;
constexpr uint8_t PIN_ROW_1 = 21;
constexpr uint8_t PIN_ROW_2 = 20;

// Arrays of pins to iterate over
const int columnPins[COLUMNS] = {PIN_COL_1, PIN_COL_2};
const int rowPins[ROWS] = {PIN_ROW_1,PIN_ROW_2};

// Buttons logic
const int keypadValues[ROWS][COLUMNS] = {{1, 2}, {3, 4}};
bool keypadStates[ROWS][COLUMNS];
bool keypadStatesPrev[ROWS][COLUMNS];
String buttonVal = "0";

// Buttons timing
unsigned long now = 0;
unsigned long buttonPressedMillis = 0;
unsigned long buttonHoldThreashold = 300;

// Lock logic
enum class lockMode {
  locked,
  unlocked,
  newPasscode
};
lockMode lockStatus;
int passcode[4] = {1, 2, 3, 4};
int passcodeInput[4] = {-1, -1, -1, -1};
int passcodeInputNum = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);

  // Initialize pins
  for (auto& c : columnPins) {
    pinMode(c, INPUT_PULLUP);
  }
  for (auto& r : rowPins) {
    pinMode(r, INPUT_PULLUP);
  }
  memset(keypadStates, 0, sizeof(keypadStates)); // Set default states of keypad
  lockStatus = lockMode::locked;
  Serial.println("BOOT!");
}

void loop() {
  updateMatrixStates();
  if (keypadStatesHasChanged()) {
    passcodeInput[passcodeInputNum++] = buttonVal.toInt(); 
    Serial.print("Button pressed: "); Serial.print(buttonVal); Serial.print("     passcodeInput: ");
    for (auto& n : passcodeInput) Serial.print(n);
    Serial.println("");
  }
  setMatrixStatesPrev();
  delay(50);
}

void updateMatrixStates() {
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

