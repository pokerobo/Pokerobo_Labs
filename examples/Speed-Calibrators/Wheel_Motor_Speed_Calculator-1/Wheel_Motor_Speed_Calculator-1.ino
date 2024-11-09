#include <Arduino.h>
#include "TimerOne.h"

const byte MOTOR1 = 2;
const byte MOTOR2 = 3;

unsigned int counter1 = 0;
unsigned int counter2 = 0;

float diskslots = 20;

void ISR_count1() {
  counter1++;  // increment Motor A counter value
} 

void ISR_count2() {
  counter2++;  // increment Motor B counter value
} 

void ISR_calculateRPM() {
  Timer1.detachInterrupt();

  Serial.print("Speed of Motor A: ");
  float rotation1 = (counter1 / diskslots) * 60.00;
  Serial.print(rotation1);
  Serial.print(" RPM");
  counter1 = 0;  //  reset counter1

  Serial.print(" - ");

  Serial.print("Speed of Motor B: ");
  float rotation2 = (counter2 / diskslots) * 60.00;
  Serial.print(rotation2);
  Serial.println(" RPM");
  counter2 = 0;  //  reset counter2

  Timer1.attachInterrupt(ISR_calculateRPM);
}

void setup() {
  Serial.begin(57600);

  Timer1.initialize(1000000); // set timer for 1sec

  attachInterrupt(digitalPinToInterrupt(MOTOR1), ISR_count1, RISING);
  attachInterrupt(digitalPinToInterrupt(MOTOR2), ISR_count2, RISING);

  Timer1.attachInterrupt(ISR_calculateRPM);
}

void loop() { }
