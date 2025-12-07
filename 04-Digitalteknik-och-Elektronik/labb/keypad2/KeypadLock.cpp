#include "KeypadLock.h"

KeypadLock::KeypadLock() {
  // Initialize pins
  for (auto& c : columnPins) {
    pinMode(c, INPUT_PULLUP);
  }
  for (auto& r : rowPins) {
    pinMode(r, INPUT_PULLUP);
  }
  memset(keypadStates, 0, sizeof(keypadStates)); // Set default states of keypad
  lockStatus = lockMode::locked;
}

void KeypadLock::update() {
  updateMatrixStates();
  checkStateChanges();
  setMatrixStatesPrev();
}

bool KeypadLock::buttonPressed() const {
  return this->pressed;
}
bool KeypadLock::buttonHeld() const {
  return this->held;
}

void KeypadLock::checkStateChanges() {
  now = millis();
  for (int c = 0; c < COLUMNS; c++) {
    for (int r = 0; r < ROWS; r++) {
      if (keypadStatesPrev[r][c] == false && keypadStates[r][c] == true) {
        buttonPressedMillis = now;
      }
      if (keypadStatesPrev[r][c] == true && keypadStates[r][c] == false && now - buttonPressedMillis >= buttonHoldThreashold) {
        Serial.print("Hold: "); Serial.print(buttonVal);
        held = true;
        return;
      } else if (keypadStatesPrev[r][c] == true && keypadStates[r][c] == false) {
        Serial.print("Pressed: "); Serial.print(buttonVal);
        pressed = true;
        return;
      }
    }
  }
  pressed = false;
  held = false;
}

void KeypadLock::updateMatrixStates() {
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

void KeypadLock::setMatrixStatesPrev() {
  for (int c = 0; c < COLUMNS; c++) {
    for (int r = 0; r < ROWS; r++) {
      keypadStatesPrev[r][c] = keypadStates[r][c];
    }
  }
}