#include "Pokerobo_Lab_Display_Handler.h"

#define PLAYER_HUMAN          0
#define PLAYER_MACHINE        1

GeometryDisplayHandler dh;

JoystickHandler joystickHandler;
JoystickAction action;

int8_t _board[3][3] = { 0 };

int top = 2;
int left = 10;
int cellWidth = 19;
int radius = cellWidth/2 - 1;

char playersTurn = PLAYER_HUMAN;
int8_t _playerFocusX = 0;
int8_t _playerFocusY = 0;

void moveFocusLeft(bool clicked) {
  if (!clicked) return;
  _playerFocusX = (_playerFocusX == 0) ? _playerFocusX : _playerFocusX - 1;
}

void moveFocusRight(bool clicked) {
  if (!clicked) return;
  _playerFocusX = (_playerFocusX < 2) ? _playerFocusX + 1 : _playerFocusX;
}

void moveFocusUp(bool clicked) {
  if (!clicked) return;
  _playerFocusY = (_playerFocusY == 0) ? _playerFocusY : _playerFocusY - 1;
}

void moveFocusDown(bool clicked) {
  if (!clicked) return;
  _playerFocusY = (_playerFocusY < 2) ? _playerFocusY + 1 : _playerFocusY;
}

void drawTick(char type, int x, int y, int r) {
  switch(type) {
    case 'x':
    case 'X':
      dh.drawLine(x - r + 1, y - r + 1, x + r - 1, y + r - 1);
      dh.drawLine(x - r + 1, y + r - 1, x + r - 1, y - r + 1);
      break;
    case 'o':
    case 'O':
      dh.drawCircle(x, y, r);
      break;
  }
}

void drawTick(char type, uint8_t i, uint8_t j) {
  drawTick(type,
    left + 1 + 1 + radius + i*(cellWidth + 1),
    top + 1 + 1 + radius + j*(cellWidth + 1),
    radius - 1);
}

void drawGrid() {
  for(int i=0; i<=3; i++) {
    int8_t x1 = left - 2;
    int8_t y1 = top + i*(cellWidth + 1);
    int8_t x2 = left + 3*(cellWidth + 1) + 2;
    int8_t y2 = y1;
    dh.drawLine(x1, y1, x2, y2);
  }

  for(int j=0; j<=3; j++) {
    int8_t x1 = left + j * (cellWidth + 1);
    int8_t y1 = top - 1;
    int8_t x2 = x1;
    int8_t y2 = top + 3*(cellWidth + 1) + 1;
    dh.drawLine(x1, y1, x2, y2);
  }
}

void drawBoard() {
  for(int i=0; i<3; i++) {
    for(int j=0; j<3; j++) {
      switch(_board[i][j]) {
        case -1:
          drawTick('O', i, j);
          break;
        case 1:
          drawTick('X', i, j);
          break;
      }
    }
  }
}

void drawFocus(uint8_t i, uint8_t j) {
  int8_t x0 = left + i*(cellWidth + 1);
  int8_t y0 = top + j*(cellWidth + 1);

  int8_t x1 = x0 + 2;
  int8_t y1 = y0 + 2;
  dh.drawLine(x1, y1, x1 + 3, y1);
  dh.drawLine(x1, y1, x1, y1 + 3);

  int8_t x2 = x0 + 2 + cellWidth - 2 - 1;
  int8_t y2 = y0 + 2;
  dh.drawLine(x2, y2, x2 - 3, y2);
  dh.drawLine(x2, y2, x2, y2 + 3);

  int8_t x3 = x0 + 2 + cellWidth - 2 - 1;
  int8_t y3 = y0 + 2 + cellWidth - 2 - 1;
  dh.drawLine(x3, y3, x3 - 3, y3);
  dh.drawLine(x3, y3, x3, y3 - 3);

  int8_t x4 = x0 + 2;
  int8_t y4 = y0 + 2 + cellWidth - 2 - 1;
  dh.drawLine(x4, y4, x4 + 3, y4);
  dh.drawLine(x4, y4, x4, y4 - 3);
}

bool tick(uint8_t i, uint8_t j) {
  if (0 <= i && i <= 2 && 0 <= j && j <= 2 && _board[i][j] == 0) {
    if (playersTurn == PLAYER_HUMAN) {
      _board[i][j] = 1;
    } else
    if (playersTurn == PLAYER_MACHINE) {
      _board[i][j] = -1;
    }
  }
}

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  dh.begin();

  _board[0][1] = 1;
  _board[1][1] = -1;
  _board[1][2] = -1;
}

void loop() {
  joystickHandler.input(&action);

  if (playersTurn == PLAYER_HUMAN) {
    moveFocusLeft(action.isButtonClicked(MASK_LEFT_BUTTON));
    moveFocusRight(action.isButtonClicked(MASK_RIGHT_BUTTON));
    moveFocusUp(action.isButtonClicked(MASK_UP_BUTTON));
    moveFocusDown(action.isButtonClicked(MASK_DOWN_BUTTON));

    if (action.isButtonClicked(MASK_ANALOG_BUTTON)) {
      tick(_playerFocusX, _playerFocusY);
    }
  }

  dh.firstPage();
  do {
    drawGrid();
    drawBoard();
    if (playersTurn == PLAYER_HUMAN) {
      drawFocus(_playerFocusX, _playerFocusY);
    }
  } while (dh.nextPage());

  delay(50);
}
