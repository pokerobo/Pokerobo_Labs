#include <Arduino.h>

int R_LED = 13; //Red light
int Y_LED = 12; //Yellow light
int G_LED = 11; //Green light

void setup() {
  pinMode(R_LED, OUTPUT);
  pinMode(Y_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
}

void loop() {
  // Green light: go
  digitalWrite(R_LED, LOW);
  digitalWrite(Y_LED, LOW);
  digitalWrite(G_LED, HIGH);
  delay(30000); //wait 30 seocnds

  // Yellow light: red light is coming
  digitalWrite(R_LED, LOW);
  digitalWrite(Y_LED, HIGH);
  digitalWrite(G_LED, LOW);
  delay(2000); //wait 2 seocnds

  // Red light: stop
  digitalWrite(R_LED, HIGH);
  digitalWrite(Y_LED, LOW);
  digitalWrite(G_LED, LOW);
  delay(30000); //wait 30 seocnds

  // Green light is coming
  digitalWrite(R_LED, HIGH);
  digitalWrite(Y_LED, HIGH);
  digitalWrite(G_LED, LOW);
  delay(2000); //wait 2 seocnds
}
