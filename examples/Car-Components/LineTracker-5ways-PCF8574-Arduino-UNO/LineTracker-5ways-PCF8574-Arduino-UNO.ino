#include <pcf8574.h>

#define PCF8574_P0 0
#define PCF8574_P1 1
#define PCF8574_P2 2
#define PCF8574_P3 3
#define PCF8574_P4 4

PCF8574 ex0(0x20);

int IRvalue1 = 0;
int IRvalue2 = 0;
int IRvalue3 = 0;
int IRvalue4 = 0;
int IRvalue5 = 0;

void setup() {
  delay(200);
  Serial.begin(115200);
  pinMode(ex0, PCF8574_P0, INPUT);
  pinMode(ex0, PCF8574_P1, INPUT);
  pinMode(ex0, PCF8574_P2, INPUT);
  pinMode(ex0, PCF8574_P3, INPUT);
  pinMode(ex0, PCF8574_P4, INPUT);
}

void loop() {
  IRvalue1 = digitalRead(ex0, PCF8574_P0);
  IRvalue2 = digitalRead(ex0, PCF8574_P1);
  IRvalue3 = digitalRead(ex0, PCF8574_P2);
  IRvalue4 = digitalRead(ex0, PCF8574_P3);
  IRvalue5 = digitalRead(ex0, PCF8574_P4);

  Serial.print("Digital Reading=");
  Serial.print(IRvalue1);
  Serial.print(IRvalue2);
  Serial.print(IRvalue3);
  Serial.print(IRvalue4);
  Serial.print(IRvalue5);
  Serial.println();
  delay(1000);
}
