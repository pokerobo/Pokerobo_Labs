#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Welcome to Pokerobo ");
}

void loop() {
  for (int i = 0; i < 13; i++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }

  for (int i = 0; i < 29; i++) {
    lcd.scrollDisplayRight();
    delay(300);
  }

  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }

  delay(1000);
}
