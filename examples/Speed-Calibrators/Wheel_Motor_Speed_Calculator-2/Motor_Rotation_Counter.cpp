#include "Motor_Rotation_Counter.h"

MotorRotationCounter::MotorRotationCounter (const byte whichISR, const byte diskslots)
    : whichISR_ (whichISR), diskslots_ (diskslots) {
  counter_ = 0;
}

void MotorRotationCounter::begin () {
  switch (whichISR_) {
    case 0:
      attachInterrupt (0, isr0, FALLING); 
      instance0_ = this;
      break;
    case 1:
      attachInterrupt (1, isr1, FALLING); 
      instance1_ = this;
      break;
  } 
}

void MotorRotationCounter::isr0 () {
  instance0_->handleInterrupt ();  
}

void MotorRotationCounter::isr1 () {
  instance1_->handleInterrupt ();  
}

float MotorRotationCounter::calculateRPM () {
  return (counter_ / diskslots_) * 60.00;
}

void MotorRotationCounter::handleInterrupt () {
  counter_++;
}

void MotorRotationCounter::resetCounter () {
  counter_ = 0;
}

MotorRotationCounter * MotorRotationCounter::instance0_;
MotorRotationCounter * MotorRotationCounter::instance1_;
