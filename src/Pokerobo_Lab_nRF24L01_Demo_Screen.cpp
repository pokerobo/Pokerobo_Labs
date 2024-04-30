#include <Pokerobo_RCB_master.h>
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

//-------------------------------------------------------------------------------------------------

uint32_t JoystickEventPacket::getCounter() {
  return _counter;
}

uint16_t JoystickEventPacket::getX() {
  return _x;
}

uint16_t JoystickEventPacket::getY() {
  return _y;
}

uint16_t JoystickEventPacket::getPressFlags() {
  return _pressFlags;
}

JoystickEventGenerator::JoystickEventGenerator(JoystickHandler* joystickHandler) {
  _joystickHandler = joystickHandler;
}

CaroMessagePacket* JoystickEventGenerator::createMessage(CaroMessagePacket *packet) {
  if (packet == NULL) {
    return packet;
  }

  JoystickEventPacket* _packet = (JoystickEventPacket*) packet;

  JoystickAction action;
  _joystickHandler->input(&action);

  _packet->_counter++;
  _packet->_x = action.getX();
  _packet->_y = action.getY();
  _packet->_pressFlags = action.getPressingFlags();

  return packet;
}

char* JoystickEventSerializer::encode(char *payload, CaroMessagePacket *packet) {
  if (payload == NULL || packet == NULL) {
    return payload;
  }
  JoystickEventPacket* _packet = (JoystickEventPacket*) packet;
  sprintf(payload, "J,%ld,%d,%d,%d", _packet->_counter, _packet->_x, _packet->_y,
      _packet->_pressFlags);

  return payload;
}

CaroMessagePacket* JoystickEventSerializer::decode(CaroMessagePacket *packet, char *payload) {
  if (payload == NULL || packet == NULL) {
    return packet;
  }

  JoystickEventPacket* _packet = (JoystickEventPacket*) packet;
  sscanf(payload, "J,%ld,%d,%d,%d", &(_packet->_counter), &(_packet->_x), &(_packet->_y),
      &(_packet->_pressFlags));

  return packet;
}

void JoystickEventDisplayHandler::renderMessageInternal(CaroMessagePacket *packet) {
  U8G2 *_u8g2 = (U8G2*)_u8g2Ref;
  int8_t _charHeight = _u8g2->getMaxCharHeight();
  int8_t _charWidth = _u8g2->getMaxCharWidth();
  if (packet == NULL) {
    return packet;
  }

  JoystickEventPacket* _packet = (JoystickEventPacket*) packet;
  sprintf(_lines[0], "Counter: %d", _packet->getCounter());
  sprintf(_lines[1], "      X: %d", _packet->getX());
  sprintf(_lines[2], "      Y: %d", _packet->getY());
  sprintf(_lines[3], "  Flags: %d", _packet->getPressFlags());

  _u8g2->drawStr(64 - 10*_charWidth, 32 - 1*_charHeight, _lines[0]);
  _u8g2->drawStr(64 - 10*_charWidth, 32 - 0*_charHeight, _lines[1]);
  _u8g2->drawStr(64 - 10*_charWidth, 32 + 1*_charHeight, _lines[2]);
  _u8g2->drawStr(64 - 10*_charWidth, 32 + 2*_charHeight, _lines[3]);
}