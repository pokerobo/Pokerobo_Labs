#include "Pokerobo_Lab_nRF24L01_Demo_Screen.h"

SimpleDisplayHandler::SimpleDisplayHandler(char *title): DisplayHandler() {
  _title = title;
}
void SimpleDisplayHandler::renderMessage(char *text) {
  U8G2 *_u8g2 = (U8G2*)_u8g2Ref;
  int8_t _charHeight = _u8g2->getMaxCharHeight();
  int8_t _charWidth = _u8g2->getMaxCharWidth();
  this->firstPage();
  do {
    _u8g2->drawFrame(1, _charHeight + 1, 128 - 2, 64 - _charHeight - 2);
    if (_title != NULL) {
      _u8g2->drawStr(64 - _charWidth * strlen(_title) / 2, _charHeight, _title);
    }
    _u8g2->drawStr(64 - _charWidth * strlen(text) / 2, 32 + _charHeight / 2, text);
  } while (this->nextPage());
}
