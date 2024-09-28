#include <Arduino.h>

const int pinOUT1 = 8;
const int pinOUT2 = 9;
const int pinOUT3 = 10;
const int pinOUT4 = 11;
const int pinOUT5 = 12;
int IRvalue1 = 0;
int IRvalue2 = 0;
int IRvalue3 = 0;
int IRvalue4 = 0;
int IRvalue5 = 0;

void setup()
{
  Serial.begin(57600);
  pinMode(pinOUT1,INPUT);
  pinMode(pinOUT2,INPUT);
  pinMode(pinOUT3,INPUT);
  pinMode(pinOUT4,INPUT);
  pinMode(pinOUT5,INPUT);
}

void loop()
{
  Serial.print("Digital Reading=");
  Serial.print(IRvalue1);
  Serial.print(IRvalue2);
  Serial.print(IRvalue3);
  Serial.print(IRvalue4);
  Serial.print(IRvalue5);
  Serial.println();
  delay(1000);
  
  IRvalue1 = digitalRead(pinOUT1);
  IRvalue2 = digitalRead(pinOUT2);
  IRvalue3 = digitalRead(pinOUT3);
  IRvalue4 = digitalRead(pinOUT4);
  IRvalue5 = digitalRead(pinOUT5);
}

