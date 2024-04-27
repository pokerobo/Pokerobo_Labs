#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Pokerobo_RCB_master.h>
#include <U8g2lib.h>

const char *title = "Transmitter";

class CaroDisplayHandler: public DisplayHandler {
  public:
    void renderMessage(char *text) {
      U8G2 *_u8g2 = (U8G2*)_u8g2Ref;
      int8_t _charHeight = _u8g2->getMaxCharHeight();
      int8_t _charWidth = _u8g2->getMaxCharWidth();
      this->firstPage();
      do {
        _u8g2->drawStr(64 - _charWidth * strlen(title) / 2, _charHeight + 1, title);
        _u8g2->drawStr(64 - _charWidth * strlen(text) / 2, 32 + _charHeight / 2, text);
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
  rf24.openWritingPipe(address);
  rf24.stopListening();

  displayHandler.begin();
}

void createMessage(char *text);

void loop() {
  const char text[20];
  createMessage(text);
  displayHandler.renderMessage(text);
  rf24.write(&text, sizeof(text));

  delay(1000);
}

int count = 0;

void createMessage(char *text) {
  count = count + 1;
  sprintf(text, "Counter: %d", count);
}
