#define DECODE_NEC
#define DECODE_PANASONIC
#define DECODE_SONY

#include "Pokerobo_Lab_IRremote_Demo.h"

IrConverterDisplayHandler displayHandler;

const int keysTotal = 18;

uint16_t mappingPanasonic[keysTotal] = { // PANASONIC - 11
  0x34,  // BIT_UP_BUTTON
  0x20,  // BIT_RIGHT_BUTTON
  0x35,  // BIT_DOWN_BUTTON
  0x21,  // BIT_LEFT_BUTTON
  0x49,  // BIT_OK_BUTTON
  0x39,  // BIT_ASTERISK_BUTTON
  0x3B,  // BIT_SHARP_BUTTON
  0x19,  // BIT_DIGIT0_BUTTON
  0x10,  // BIT_DIGIT1_BUTTON
  0x11,  // BIT_DIGIT2_BUTTON
  0x12,  // BIT_DIGIT3_BUTTON
  0x13,  // BIT_DIGIT4_BUTTON
  0x14,  // BIT_DIGIT5_BUTTON
  0x15,  // BIT_DIGIT6_BUTTON
  0x16,  // BIT_DIGIT7_BUTTON
  0x17,  // BIT_DIGIT8_BUTTON
  0x18,  // BIT_DIGIT9_BUTTON
  0x3D,
};

uint16_t mappingSony[keysTotal] = { // SONY (23)
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
  0x15,
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

void logMapping(uint16_t sCommand, int keyIndex, uint16_t tCommand) {
  Serial.print("source command: "), Serial.print(sCommand, HEX);
  Serial.print(" -> index: "), Serial.print(keyIndex);
  Serial.print(" => target command: "), Serial.print(tCommand, HEX);
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
    IRData decodedIRData = IrReceiver.decodedIRData;

    bool found = false;
    if (decodedIRData.protocol == PANASONIC) {
      int keyIndex = findIndex(keysTotal, &mappingPanasonic[0], decodedIRData.command);
      if (keyIndex >= 0) {
        uint16_t tCommand = mappingSony[keyIndex];
        logMapping(decodedIRData.command, keyIndex, tCommand);
        IrSender.write(SONY, 0x1, tCommand, 2);
        displayHandler.renderConversion(&decodedIRData, SONY, 0x1, tCommand);
        found = true;
      }
    }
    if (!found) {
      displayHandler.renderMessage(&decodedIRData);
    }

    IrReceiver.resume();
  }
  delay(100);
}
