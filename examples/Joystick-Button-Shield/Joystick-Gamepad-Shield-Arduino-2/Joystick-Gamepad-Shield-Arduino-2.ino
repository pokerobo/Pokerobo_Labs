#include <Arduino.h>

// JoyStick Shield pins
const int A_pin = 2, B_pin = 3, C_pin = 4, D_pin = 5, E_pin = 6, F_pin = 7;
const int JoyStick_pin = 8;
const int X_pin = A0, Y_pin = A1;

const int buttons[] = { A_pin, B_pin, C_pin, D_pin, E_pin, F_pin, JoyStick_pin };

void setup() {
  Serial.begin(57600);
  for (int i = 0; i < 7; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void loop() {
  int x = analogRead(X_pin);
  int y = analogRead(Y_pin);
  
  int buttonStates = 0;

  for (int i = 0; i < 7; i++) {
    buttonStates |= ((digitalRead(buttons[i]) == LOW) ? 1 : 0) << i;
  }

  Serial.println("S" + String(x) + "," + String(y) + "," + String(buttonStates));

  delay(500);
}
