#include <Arduino.h>

int R_PIN =  9; // select the pin for the red LED
int G_PIN = 10; // select the pin for the green LED
int B_PIN = 11; // select the pin for the  blue LED

void setup() {
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  Serial.begin(57600);
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
