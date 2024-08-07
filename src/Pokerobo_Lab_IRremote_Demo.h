#ifndef __POKEROBO_LAB_IRREMOTE_DEMO_H__
#define __POKEROBO_LAB_IRREMOTE_DEMO_H__

#include "Pokerobo_Lab_Display_Handler.h"
#include <IRremote.hpp>

char* toString(decode_type_t protocol);

class IrReceiverDisplayHandler: public GeometryDisplayHandler {
  public:
    using GeometryDisplayHandler::GeometryDisplayHandler;
    IrReceiverDisplayHandler(): GeometryDisplayHandler() {
      _title = "IR Receiver";
    }
    void renderMessage(char *text);
    void renderMessage(IRData *irData);
  protected:
    virtual void renderFrame();
    virtual void renderTitle();
    virtual void prepareIrData(IRData *irData);
    virtual void renderIrData(IRData *irData);
  private:
    void renderMessageOrString(IRData *irData, char *text);
    char *_title = NULL;
    char _lines[2][32] = { {0}, {0} };
};

void IrReceiverDisplayHandler::renderMessage(char *text) {
  this->renderMessageOrString(NULL, text);
}

void IrReceiverDisplayHandler::renderMessage(IRData *irData) {
  this->renderMessageOrString(irData, NULL);
}

void IrReceiverDisplayHandler::renderMessageOrString(IRData *irData, char *text) {
  int8_t _charHeight = this->getMaxCharHeight();
  int8_t _charWidth = this->getMaxCharWidth();
  if (irData != NULL) {
    this->prepareIrData(irData);
  }
  this->firstPage();
  do {
    this->renderFrame();
    this->renderTitle();
    if (irData != NULL) {
      this->renderIrData(irData);
    } else if (text != NULL) {
      this->drawStr(64 - _charWidth * strlen(text) / 2, 32 + _charHeight / 2, text);
    }
  } while (this->nextPage());
}

void IrReceiverDisplayHandler::renderFrame() {
  int8_t _charHeight = this->getMaxCharHeight();
  int8_t _charWidth = this->getMaxCharWidth();
  this->drawFrame(1, _charHeight + 1, 128 - 2, 64 - _charHeight - 2);
}

void IrReceiverDisplayHandler::renderTitle() {
  if (_title != NULL) {
    int8_t _charHeight = this->getMaxCharHeight();
    int8_t _charWidth = this->getMaxCharWidth();
    this->drawStr(64 - _charWidth * strlen(_title) / 2, _charHeight - 1, _title);
  }
}

void IrReceiverDisplayHandler::prepareIrData(IRData *irData) {
  sprintf(_lines[0], "P:%s", toString(irData->protocol));
  sprintf(_lines[1], "C:0x%X/0x%lX", irData->command, irData->decodedRawData);
}

void IrReceiverDisplayHandler::renderIrData(IRData *irData) {
  this->drawStr(10, 32, _lines[0]);
  this->drawStr(10, 32 + 12, _lines[1]);
}

char* toString(decode_type_t protocol) {
  switch (protocol) {
    case APPLE: return "APPLE";
    case NEC: return "NEC";
    case NEC2: return "NEC2";
    case SONY: return "SONY";
    case PANASONIC: return "PANASONIC";
    case SHARP: return "SHARP";
    case JVC: return "JVC";
    case SAMSUNG: return "SAMSUNG";
    case SAMSUNG48: return "SAMSUNG48";
    case SAMSUNGLG: return "SAMSUNGLG";
    case LG: return "LG";
    case LG2: return "LG2";
    case RC5: return "RC5";
    case RC6: return "RC6";
    case DENON: return "DENON";
    case ONKYO: return "ONKYO";
    case KASEIKYO: return "KASEIKYO";
    case KASEIKYO_DENON: return "KASEIKYO_DENON";
    case KASEIKYO_SHARP: return "KASEIKYO_SHARP";
    case KASEIKYO_JVC: return "KASEIKYO_JVC";
    case KASEIKYO_MITSUBISHI: return "KASEIKYO_MITSUBISHI";
    case PULSE_WIDTH: return "PULSE_WIDTH";
    case PULSE_DISTANCE: return "PULSE_DISTANCE";
    case BANG_OLUFSEN: return "BANG_OLUFSEN";
    case BOSEWAVE: return "BOSEWAVE";
    case LEGO_PF: return "LEGO_PF";
    case MAGIQUEST: return "MAGIQUEST";
    case WHYNTER: return "WHYNTER";
    case FAST: return "FAST";
    case UNKNOWN: return "UNKNOWN";
    default:
      return "NOOP";
  }
}

bool checkKeyPress(IRData *decodedIRData) {
  bool ok = true;
  switch (decodedIRData->protocol) {
    case UNKNOWN:
      ok = false;
      break;
    case SONY:
      switch (decodedIRData->command) {
        case 0x74:
          Serial.println("UP");
          break;
        case 0x33:
          Serial.println("RIGHT");
          break;
        case 0x75:
          Serial.println("DOWN");
          break;
        case 0x34:
          Serial.println("LEFT");
          break;
      };
      break;
    case NEC:
      uint32_t rawData = decodedIRData->decodedRawData;
      switch(rawData) {
        case 0xBA45FF00:
          Serial.println("1");
          break;
        case 0xB946FF00:
          Serial.println("2");
          break;
        case 0xB847FF00:
          Serial.println("3");
          break;
        case 0xBB44FF00:
          Serial.println("4");
          break;
        case 0xBF40FF00:
          Serial.println("5");
          break;
        case 0xBC43FF00:
          Serial.println("6");
          break;
        case 0xF807FF00:
          Serial.println("7");
          break;
        case 0xEA15FF00:
          Serial.println("8");
          break;
        case 0xF609FF00:
          Serial.println("9");
          break;
        case 0xE916FF00:
          Serial.println("*");
          break;
        case 0xE619FF00:
          Serial.println("0");
          break;
        case 0xF20DFF00:
          Serial.println("#");
          break;
        case 0xE718FF00:
          Serial.println("UP");
          break;
        case 0xF708FF00:
          Serial.println("LEFT");
          break;
        case 0xE31CFF00:
          Serial.println("OK");
          break;
        case 0xA55AFF00:
          Serial.println("RIGHT");
          break;
        case 0xAD52FF00:
          Serial.println("DOWN");
          break;
        default:
          Serial.println("NOOP");
      }
      break;
    default:
      ok = false;
  }
  return ok;
}

#endif
