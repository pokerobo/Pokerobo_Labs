#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

int maxX, maxY, height;
uint8_t counter[128] = { 0 };
uint8_t maxCount = 0, minCount = 0;
uint16_t total = 0;
bool stopped = false;

void setup() {
  randomSeed(analogRead(A3));
  Serial.begin(57600);
  displayHandler.begin();
  maxX = displayHandler.getMaxX();
  maxY = displayHandler.getMaxY();
  height = maxY - displayHandler.getMaxCharHeight() - 1;
}

void loop() {
  if (stopped) return;

  total++;

  uint8_t val = random(0, maxX+1);

  if (counter[val] == minCount) {
    counter[val]++;
    uint8_t n = 0;
    for(int i=0; i<=maxX; i++) {
      if (counter[i] <= minCount) {
        n++;
        break;
      }
    }
    if (n == 0) {
      minCount = counter[val];
    }
  } else {
    counter[val]++;
  }

  if (counter[val] > maxCount) {
    maxCount = counter[val];
  }

  if (maxCount > height - 5) {
    uint8_t minCount = maxCount;
    for(int i=0; i<=maxX; i++) {
      if (counter[i] < minCount) {
        minCount = counter[i];
      }
    }
    if (minCount > 0) {
      for(int i=0; i<=maxX; i++) {
        counter[i] -= minCount;
      }
      maxCount -= minCount;
      minCount = 0;
    }
  }

  if (maxCount > height) {
    stopped = true;
    return;
  }

  char text[36] = { 0 };
  sprintf(text, "#% 5d min:%2d max:%2d H:%2d", total, minCount, maxCount, height);

  displayHandler.firstPage();
  do {
    displayHandler.drawStr(0, maxY, text);
    for(int i=0; i<=127; i++) {
      displayHandler.drawLine(i, height - counter[i], i, height);
    }
  } while (displayHandler.nextPage());
}
