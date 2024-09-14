#include <Arduino.h>

const int pinOuts[] = { 8, 9, 10, 11, 12 };
int irVals[] = { 0 };

void setup() {
  Serial.begin(57600);
  for(int i=0; i<5; i++) {
    pinMode(pinOuts[i], INPUT);
  }
}

void loop() {
  for(int i=0; i<5; i++) {
    irVals[i] = digitalRead(pinOuts[i]);
  }
  Serial.print("Digital Reading=");
  for(int i=0; i<5; i++) {
    Serial.print(irVals[i]);
  }
  Serial.println();
  delay(1000);
}
