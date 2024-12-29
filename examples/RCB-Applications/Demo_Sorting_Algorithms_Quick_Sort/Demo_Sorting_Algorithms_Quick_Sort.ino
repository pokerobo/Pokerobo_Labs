#include "SortingRunner_Implementation.h"

GeometryDisplayHandler pen;
SampleManager sample(&pen);
QuickSortingRunner runner(&sample);

void setup() {
  Serial.begin(57600);
  pen.begin();
  sample.begin();
  runner.sort();
}

void loop() {}
