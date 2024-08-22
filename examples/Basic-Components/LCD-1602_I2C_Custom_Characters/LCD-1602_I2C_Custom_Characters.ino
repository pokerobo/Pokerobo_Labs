// https://maxpromer.github.io/LCD-Character-Creator/
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte customChar[] = {
  B00100,
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B01010,
  B00000
};

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.createChar(0, customChar);
  lcd.home();
  lcd.write(0);
}

void loop() { }
