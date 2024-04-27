#include "Pokerobo_Lab_nRF24L01_Demo_Screen.h"

void CaroMessageGenerator::createMessage(char *text) {
  _count = _count + 1;
  sprintf(text, "Counter: %d", _count);
}

CaroMessagePacket* CaroMessageGenerator::createMessage(CaroMessagePacket *packet) {
  return packet;
}

CaroDisplayHandler::CaroDisplayHandler(char *title): DisplayHandler() {
  _title = title;
}

void CaroDisplayHandler::renderMessage(char *text) {
  this->renderMessageOrString(NULL, text);
}

void CaroDisplayHandler::renderMessage(CaroMessagePacket *packet) {
  this->renderMessageOrString(packet, NULL);
}

void CaroDisplayHandler::renderMessageOrString(CaroMessagePacket *packet, char *text) {
  U8G2 *_u8g2 = (U8G2*)_u8g2Ref;
  int8_t _charHeight = _u8g2->getMaxCharHeight();
  int8_t _charWidth = _u8g2->getMaxCharWidth();
  this->firstPage();
  do {
    _u8g2->drawFrame(1, _charHeight + 1, 128 - 2, 64 - _charHeight - 2);
    if (_title != NULL) {
      _u8g2->drawStr(64 - _charWidth * strlen(_title) / 2, _charHeight, _title);
    }
    if (text != NULL) {
      _u8g2->drawStr(64 - _charWidth * strlen(text) / 2, 32 + _charHeight / 2, text);
    } else if (packet != NULL) {
      this->renderMessageInternal(packet);
    }
  } while (this->nextPage());
}

void CaroDisplayHandler::renderMessageInternal(CaroMessagePacket *packet) {
  // implementing here
}

//-------------------------------------------------------------------------------------------------

char* CounterMessagePacket::getContent() {
  return _content;
}

void CounterMessagePacket::update(const char* payload) {
  strcpy(_content, payload);
}

CaroMessagePacket* CounterMessageGenerator::createMessage(CaroMessagePacket *packet) {
  if (packet == NULL) {
    return packet;
  }

  _count = _count + 1;

  CounterMessagePacket* _packet = (CounterMessagePacket*) packet;
  sprintf(_packet->_content, "Counter: %d", _count);

  return packet;
}

char* CounterMessageSerializer::encode(char *payload, CaroMessagePacket *packet) {
  if (payload == NULL || packet == NULL) {
    return payload;
  }
  CounterMessagePacket* _packet = (CounterMessagePacket*) packet;
  strcpy(payload, _packet->_content);
}

CaroMessagePacket* CounterMessageSerializer::decode(CaroMessagePacket *packet, char *payload) {
  if (payload == NULL || packet == NULL) {
    return packet;
  }

  CounterMessagePacket* _packet = (CounterMessagePacket*) packet;
  strcpy(_packet->_content, payload);

  return packet;
}

void CounterDisplayHandler::renderMessageInternal(CaroMessagePacket *packet) {
  U8G2 *_u8g2 = (U8G2*)_u8g2Ref;
  int8_t _charHeight = _u8g2->getMaxCharHeight();
  int8_t _charWidth = _u8g2->getMaxCharWidth();
  if (packet != NULL) {
    CounterMessagePacket* _packet = (CounterMessagePacket*) packet;
    char *text = _packet->getContent();
    _u8g2->drawStr(64 - _charWidth * strlen(text) / 2, 32 + _charHeight / 2, text);
  }
}
