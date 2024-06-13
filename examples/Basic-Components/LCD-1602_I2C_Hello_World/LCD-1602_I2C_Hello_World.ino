#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(2,0);
  lcd.print("Hello world!");

  lcd.setCursor(2,1);
  lcd.print("LCD Tutorial");
}

void loop() {}
