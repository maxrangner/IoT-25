#include "defines.h"
#include "KeypadLock.h"

KeypadLock lock;

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);
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







