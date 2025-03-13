#include "Pokerobo_Lab_SortingRunners.h"

JoystickHandler joystickHandler;
GeometryDisplayHandler displayHandler;

SampleManager sample(&displayHandler);

ProgramSelector programSelector(&displayHandler, &joystickHandler, SCREEN_FLOW_CONFIGURATION);

void setup() {
  Serial.begin(57600);

  joystickHandler.begin();
  displayHandler.begin();

  sample.begin();

  programSelector.add(new BubbleSortingRunner(&sample));
  programSelector.add(new InsertionSortingRunner(&sample));
  programSelector.add(new SelectionSortingRunner(&sample));
  programSelector.add(new MergeSortingRunner(&sample));
  programSelector.add(new QuickSortingRunner(&sample));
  programSelector.add(new HeapSortingRunner(&sample));

  programSelector.begin();
}

void loop() {
  programSelector.check();
}
