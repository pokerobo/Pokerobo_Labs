#include <Arduino.h>

void setup() {
  Serial.begin(57600);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(2), sw1Clicked, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), sw2Clicked, RISING);
}

void loop() {}

void sw1Clicked() {
  Serial.println("SW1 is clicked");
}

void sw2Clicked() {
  Serial.println("SW2 is clicked");
}
