#include <RF24.h>
#include "Pokerobo_Lab_Display_Handler.h"

class CaroDisplayHandler: public GeometryDisplayHandler {
  public:
    void renderMessage(char *text) {
      this->firstPage();
      do {
        this->drawStr(0, 32, text);
      } while (this->nextPage());
    }
};

const uint64_t address = 0x123456789ABCDEF0LL;
const uint8_t pin_ce = 9;
const uint8_t pin_csn = 10;

RF24 rf24(pin_ce, pin_csn);
CaroDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);

  rf24.begin();
  rf24.openReadingPipe(0, address);
  rf24.startListening();

  displayHandler.begin();
}

void loop() {
  if (rf24.available()) {
    char text[20] = {0};
    rf24.read(&text, sizeof(text));
    displayHandler.renderMessage(text);
    delay(100);
  }
}
