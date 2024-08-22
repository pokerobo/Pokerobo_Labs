#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int counter = 0;
char line[17] = {};

void setup() {
  lcd.init();
  lcd.clear();
  lcd.noBacklight();

  lcd.setCursor(0, 0);
  lcd.print("LCD1602 Tutorial");
}

void loop() {
  sprintf(line, "Counter: %5d", ++counter);
  lcd.setCursor(0, 1);
  lcd.print(line);
  delay(100);
}
