#pragma once
#include "defines.h"

class KeypadLock {
  // Arrays of pins to iterate over
  const int columnPins[COLUMNS] = {PIN_COL_1, PIN_COL_2};
  const int rowPins[ROWS] = {PIN_ROW_1,PIN_ROW_2};

  // Buttons logic
  const int keypadValues[ROWS][COLUMNS] = {{1, 2}, {3, 4}};
  bool keypadStates[ROWS][COLUMNS];
  bool keypadStatesPrev[ROWS][COLUMNS];
  int buttonVal = 0;
  bool pressed = false;
  bool held = false;

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
public:
  KeypadLock();
  void update();
  bool buttonPressed() const;
  bool buttonHeld() const;
  void checkStateChanges();
  void updateMatrixStates();
  void setMatrixStatesPrev();
};