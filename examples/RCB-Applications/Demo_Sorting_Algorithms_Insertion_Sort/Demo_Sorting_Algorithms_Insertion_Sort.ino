#include "Pokerobo_Lab_Sorting_Structure.h"

GeometryDisplayHandler pen;
SampleManager sample(&pen);
InsertionSortingRunner runner(&sample);

void setup() {
  Serial.begin(57600);
  pen.begin();
  sample.begin();
  runner.sort();
}

void loop() {}
