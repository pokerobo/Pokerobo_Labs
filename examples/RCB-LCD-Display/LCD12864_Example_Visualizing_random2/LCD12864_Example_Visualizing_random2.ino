#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

uint8_t counter[128] = { 0 };
uint8_t maxCount = 0;
bool stopped = false;

void setup() {
  randomSeed(analogRead(A3));
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  if (stopped) return;

  uint8_t val = random(0, 127+1);

  counter[val]++;
  if (counter[val] > maxCount) {
    maxCount = counter[val];
  }

  if (maxCount > 60) {
    uint8_t minCount = 127;
    for(int i=0; i<=127; i++) {
      if (counter[i] < minCount) {
        minCount = counter[i];
      }
    }
    if (minCount > 0) {
      for(int i=0; i<=127; i++) {
        counter[i] -= minCount;
      }
      maxCount -= minCount;
    }
  }

  if (maxCount > 63) {
    stopped = true;
    return;
  }

  displayHandler.firstPage();
  do {
     for(int i=0; i<=127; i++) {
      displayHandler.drawLine(i, 63 - counter[i], i, 63);
    }   
  } while (displayHandler.nextPage());
}
