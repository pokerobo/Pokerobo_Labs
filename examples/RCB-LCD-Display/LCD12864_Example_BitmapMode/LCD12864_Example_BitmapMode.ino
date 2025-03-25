#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler pen;

JoystickHandler han;
JoystickAction action;

const unsigned char dino [] PROGMEM = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80,
  0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80,
  0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80,
  0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80,
  0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x80,
  0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x80,
  0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x80,
  0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x80,
  0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80,
  0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80,
  0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80,
  0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

const int BLOCK_WIDTH = 8*8;
const int BLOCK_HEIGHT = 20;

const uint8_t BLOCK1_X = 10;
const uint8_t BLOCK1_Y = 10;

const uint8_t STEP = 2;

uint8_t bitmapMode = 0;

uint8_t block2_x = BLOCK1_X + STEP;
uint8_t block2_y = BLOCK1_Y + 2*STEP;

void setup() {
  Serial.begin(57600);
  han.begin();
  pen.begin();
}

void loop() {
  han.input(&action);

  if (action.isButtonClicked(MASK_ANALOG_BUTTON)) {
    bitmapMode = !bitmapMode;
  }

	if (action.isButtonPressed(MASK_LEFT_BUTTON)) {
		block2_x = (block2_x >= STEP) ? block2_x - STEP : 0;
	}
	if (action.isButtonPressed(MASK_RIGHT_BUTTON)) {
		block2_x = (block2_x <= 127 - BLOCK_WIDTH - STEP) ? block2_x + STEP : 127 - BLOCK_WIDTH;
	}

  if (action.isButtonPressed(MASK_UP_BUTTON)) {
		block2_y = (block2_y >= STEP) ? block2_y - STEP : 0;
	}
	if (action.isButtonPressed(MASK_DOWN_BUTTON)) {
		block2_y = (block2_y <= 63 - BLOCK_HEIGHT - STEP) ? block2_y + STEP : 63 - BLOCK_HEIGHT;
	}

  pen.firstPage();
  do {
    pen.setDrawColor(0);
    pen.setBitmapMode(bitmapMode);
    pen.drawXBMP(BLOCK1_X, BLOCK1_Y, BLOCK_WIDTH, BLOCK_HEIGHT, dino);
    pen.drawXBMP(block2_x, block2_y, BLOCK_WIDTH, BLOCK_HEIGHT, dino);
  } while (pen.nextPage());

  delay(50);
}
