#include "defines.h"
#include "KeypadLock.h"

const int columnPins[COLUMNS] = {PIN_COL_1, PIN_COL_2};
const int rowPins[ROWS] = {PIN_ROW_1,PIN_ROW_2};
KeypadLock lock;

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);
  delay(500);

  for (auto& c : columnPins) {
    Serial.print("Column pin: "); Serial.println(c);
    pinMode(c, INPUT_PULLUP);
  }
  for (auto& r : rowPins) {
    Serial.print("Row pin: "); Serial.println(r);
    pinMode(r, INPUT_PULLUP);
  }

  Serial.println("BOOT!");
}

void loop() {
  lock.update();
  if (lock.buttonPressed()) {
    Serial.println("Something pressed");
  } else if (lock.buttonHeld()) {
    Serial.println("Something held");
  }
  // updateMatrixStates();
  // if (keypadStatesHasChanged()) {
  //   passcodeInput[passcodeInputNum++] = buttonVal.toInt(); 
  //   Serial.print("Button pressed: "); Serial.print(buttonVal); Serial.print("     passcodeInput: ");
  //   for (auto& n : passcodeInput) Serial.print(n);
  //   Serial.println("");
  // }
  // setMatrixStatesPrev();
  delay(50);
}







