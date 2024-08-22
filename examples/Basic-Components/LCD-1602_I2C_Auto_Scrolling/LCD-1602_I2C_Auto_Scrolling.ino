#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.clear();
  lcd.noBacklight();
  lcd.autoscroll();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to Pokerobo");
}

void loop() {
  lcd.setCursor(0, 1);
  for (int digit = 0; digit < 10; digit++) {
    lcd.print(digit);
    lcd.print(' ');
    delay(500);
  }
}
