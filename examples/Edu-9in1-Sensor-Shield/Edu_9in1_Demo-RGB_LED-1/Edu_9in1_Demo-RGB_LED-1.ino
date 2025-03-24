#include <Arduino.h>

int R_PIN =  9;
int G_PIN = 10;
int B_PIN = 11;

void setup() {
  Serial.begin(57600);
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

void loop() {
  int val;
  for(val = 255; val > 0; val--) {
    analogWrite(R_PIN, val);
    analogWrite(G_PIN, 128 - val);
    analogWrite(B_PIN, 255 - val);
    delay(1); 
  }
  for(val = 0; val < 255; val++) {
    analogWrite(R_PIN, val);
    analogWrite(G_PIN, 128 - val);
    analogWrite(B_PIN, 255 - val);
    delay(1);
  }
}
