#include <IRremote.hpp>

#define __LCD_KEYPAD_ENABLED__ 1

#if __LCD_KEYPAD_ENABLED__
#include <LiquidCrystal.h>

const int PIN_D4 = 4;
const int PIN_D5 = 5;
const int PIN_D6 = 6;
const int PIN_D7 = 7;
const int PIN_RS = 8;
const int PIN_EN = 9;
const int PIN_BL = 10;
#endif

#if __LCD_KEYPAD_ENABLED__
LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_D4, PIN_D5, PIN_D6, PIN_D7);
#endif

#if __LCD_KEYPAD_ENABLED__
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

void lcdBegin(LiquidCrystal* lcd) {
  lcd->begin(16, 2);
  lcd->setCursor(0,0);
  lcd->print("Pokerobo.COM");
  lcd->setCursor(0,1);
  lcd->print("IR Code Detector");
}

void lcdDisplay(LiquidCrystal* lcd, String lines[], int total) {
  lcd->clear();

  lcd->setCursor(0, 0);
  lcd->print(lines[0]);

  lcd->setCursor(0, 1);
  lcd->print(lines[1]);
}
#endif

void setup() {
  Serial.begin(57600);
  IrReceiver.begin(A1, ENABLE_LED_FEEDBACK);
#if __LCD_KEYPAD_ENABLED__
  lcdBegin(&lcd);
#endif
}

void loop() {
  if (IrReceiver.decode()) {
    bool ok = true;
    IRData decodedIRData = IrReceiver.decodedIRData;
    switch (decodedIRData.protocol) {
      case UNKNOWN:
        ok = false;
        break;
      case SONY:
        switch (decodedIRData.command) {
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
        uint32_t rawData = decodedIRData.decodedRawData;
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

    if (ok) {
#if __LCD_KEYPAD_ENABLED__
      char line0[32] = "";
      char line1[32] = "";

      sprintf(line0, "P:%s", toString(decodedIRData.protocol));
      sprintf(line1, "C:0x%X/0x%lX", decodedIRData.command, decodedIRData.decodedRawData);

      String lines[2];
      lines[0] = String(line0);
      lines[1] = String(line1);
      lcdDisplay(&lcd, lines, 2);
#endif
    }

    // Print complete received data in one line
    IrReceiver.printIRResultShort(&Serial);
    // Print the statement required to send this data
    IrReceiver.printIRSendUsage(&Serial);
    // Enable receiving of the next value
    IrReceiver.resume();
  } else {
    delay(100);
  }
}
