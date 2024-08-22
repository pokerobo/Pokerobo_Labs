#define DECODE_PANASONIC
#define DECODE_SONY

#include "Pokerobo_Lab_IRremote_Demo.h"

#define RC_PROTOCOL_TYPE          PANASONIC
#define RC_KEY_UP_BUTTON          0x34
#define RC_KEY_RIGHT_BUTTON       0x20
#define RC_KEY_DOWN_BUTTON        0x35
#define RC_KEY_LEFT_BUTTON        0x21
#define RC_KEY_OK_BUTTON          0x49
#define RC_KEY_ASTERISK_BUTTON    0x39
#define RC_KEY_SHARP_BUTTON       0x3B
#define RC_KEY_DIGIT0_BUTTON      0x19
#define RC_KEY_DIGIT1_BUTTON      0x10
#define RC_KEY_DIGIT2_BUTTON      0x11
#define RC_KEY_DIGIT3_BUTTON      0x12
#define RC_KEY_DIGIT4_BUTTON      0x13
#define RC_KEY_DIGIT5_BUTTON      0x14
#define RC_KEY_DIGIT6_BUTTON      0x15
#define RC_KEY_DIGIT7_BUTTON      0x16
#define RC_KEY_DIGIT8_BUTTON      0x17
#define RC_KEY_DIGIT9_BUTTON      0x18
#define RC_KEY_POWER_BUTTON       0x3D

#define TV_PROTOCOL_TYPE          SONY
#define TV_KEY_VOL_INC            0x12
#define TV_KEY_VOL_DEC            0x13
#define TV_KEY_CHANNEL_TOGGLE     0x25
#define TV_KEY_POWER_BUTTON       0x15

IrConverterDisplayHandler displayHandler;

byte sharpToggleState = 0;
byte sharpToggleTrail = 0;

const int keysTotal = 18;

uint16_t keySourceCommands[keysTotal] = { // PANASONIC - 11
  RC_KEY_UP_BUTTON,           // BIT_UP_BUTTON
  RC_KEY_RIGHT_BUTTON,        // BIT_RIGHT_BUTTON
  RC_KEY_DOWN_BUTTON,         // BIT_DOWN_BUTTON
  RC_KEY_LEFT_BUTTON,         // BIT_LEFT_BUTTON
  RC_KEY_OK_BUTTON,           // BIT_OK_BUTTON
  RC_KEY_ASTERISK_BUTTON,     // BIT_ASTERISK_BUTTON
  RC_KEY_SHARP_BUTTON,        // BIT_SHARP_BUTTON
  RC_KEY_DIGIT0_BUTTON,       // BIT_DIGIT0_BUTTON
  RC_KEY_DIGIT1_BUTTON,       // BIT_DIGIT1_BUTTON
  RC_KEY_DIGIT2_BUTTON,       // BIT_DIGIT2_BUTTON
  RC_KEY_DIGIT3_BUTTON,       // BIT_DIGIT3_BUTTON
  RC_KEY_DIGIT4_BUTTON,       // BIT_DIGIT4_BUTTON
  RC_KEY_DIGIT5_BUTTON,       // BIT_DIGIT5_BUTTON
  RC_KEY_DIGIT6_BUTTON,       // BIT_DIGIT6_BUTTON
  RC_KEY_DIGIT7_BUTTON,       // BIT_DIGIT7_BUTTON
  RC_KEY_DIGIT8_BUTTON,       // BIT_DIGIT8_BUTTON
  RC_KEY_DIGIT9_BUTTON,       // BIT_DIGIT9_BUTTON
  RC_KEY_POWER_BUTTON,
};

uint16_t keyTargetCommands[keysTotal] = { // SONY (23)
  0x74,  // BIT_UP_BUTTON
  0x33,  // BIT_RIGHT_BUTTON
  0x75,  // BIT_DOWN_BUTTON
  0x34,  // BIT_LEFT_BUTTON
  0x65,  // BIT_OK_BUTTON
  0x3A,  // BIT_ASTERISK_BUTTON
  0x3F,  // BIT_SHARP_BUTTON
  0x09,  // BIT_DIGIT0_BUTTON
  0x00,  // BIT_DIGIT1_BUTTON
  0x01,  // BIT_DIGIT2_BUTTON
  0x02,  // BIT_DIGIT3_BUTTON
  0x03,  // BIT_DIGIT4_BUTTON
  0x04,  // BIT_DIGIT5_BUTTON
  0x05,  // BIT_DIGIT6_BUTTON
  0x06,  // BIT_DIGIT7_BUTTON
  0x07,  // BIT_DIGIT8_BUTTON
  0x08,  // BIT_DIGIT9_BUTTON
  TV_KEY_POWER_BUTTON,
};

int findIndex(int total, uint16_t *mapping, uint16_t value) {
  int pos = -1;
  for (int i=0; i<total; i++) {
    if (value == mapping[i]) {
      pos = i;
      break;
    }
  }
  return pos;
}

void convert(IRData &irData, bool &found, int &codeIndex, uint16_t &tvButtonCode) {
  found = false;
  tvButtonCode = 0;

  if (irData.protocol == RC_PROTOCOL_TYPE) {
    if (irData.command == RC_KEY_SHARP_BUTTON) {
      sharpToggleState = 1 - sharpToggleState;
      if (sharpToggleState) { // sharp button is switched on
        sharpToggleTrail = 0;
        return;
      } else { // sharp button is switched off
        if (sharpToggleTrail > 0) {
          return;
        }
      }
    } else {
      if (sharpToggleState) {
        if (sharpToggleTrail < 255) {
          sharpToggleTrail++;
        }
      }
    }

    if (sharpToggleState) {
      if (irData.command == RC_KEY_ASTERISK_BUTTON) {
        sharpToggleState = 1 - sharpToggleState;
        found = true;
        tvButtonCode = TV_KEY_POWER_BUTTON;
        return;
      }
      if (irData.command == RC_KEY_UP_BUTTON) {
        found = true;
        tvButtonCode = TV_KEY_VOL_INC;
        return;
      }
      if (irData.command == RC_KEY_DOWN_BUTTON) {
        found = true;
        tvButtonCode = TV_KEY_VOL_DEC;
        return;
      }
    }

    codeIndex = findIndex(keysTotal, &keySourceCommands[0], irData.command);
    if (codeIndex >= 0) {
      found = true;
      tvButtonCode = keyTargetCommands[codeIndex];
      return;
    }
  }
}

void logMapping(uint16_t rcButtonCode, int codeIndex, uint16_t tvButtonCode) {
  Serial.print("source command: "), Serial.print(rcButtonCode, HEX);
  Serial.print(" -> index: "), Serial.print(codeIndex);
  Serial.print(" => target command: "), Serial.print(tvButtonCode, HEX);
  Serial.println();
}

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  IrSender.begin(A2, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
  IrReceiver.begin(A3, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    IRData irData = IrReceiver.decodedIRData;

    bool found = false;
    int codeIndex = -1;
    uint16_t tvButtonCode = 0;

    convert(irData, found, codeIndex, tvButtonCode);

    if (found) {
      logMapping(irData.command, codeIndex, tvButtonCode);
      IrSender.write(SONY, 0x1, tvButtonCode, 2);
      displayHandler.renderConversion(&irData, SONY, 0x1, tvButtonCode);
    } else {
      displayHandler.renderMessage(&irData);
    }

    IrReceiver.resume();
  }
  delay(100);
}
