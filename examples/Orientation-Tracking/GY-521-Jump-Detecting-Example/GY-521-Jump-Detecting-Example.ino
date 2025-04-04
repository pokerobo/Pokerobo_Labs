#include <Wire.h>
#include <MPU6050.h>

#include "Pokerobo_Lab_MPU_AcceGyroRenderer.h"
#include "Pokerobo_Lab_MPU_JumpingDetector.h"

#if defined(ARDUINO_UNOR4_WIFI)
#include "Pokerobo_Lab_MPU_EventToKeyboard.h"
#endif

JoystickHandler joystickHandler;
GeometryDisplayHandler displayHandler;
AcceGyroRenderer acceGyroRenderer(&displayHandler);
#if defined(ARDUINO_UNOR4_WIFI)
JumpingToKeyboardListener eventListener;
#else
JumpingListener eventListener;
#endif
JumpingDetectorSerialLog detector(&displayHandler,
    &acceGyroRenderer,
    &eventListener);

ProgramSelector programSelector(&displayHandler, &joystickHandler, SCREEN_FLOW_CONFIGURATION);

MPU6050 mpu;

int16_t ax, ay, az;  // Gia tốc trên các trục

void setup() {
  // Khởi tạo giao tiếp I2C
  Wire.begin();
  Serial.begin(57600);

  joystickHandler.begin();
  displayHandler.begin();

  // Khởi tạo MPU6500
  mpu.initialize();
  
  // Kiểm tra xem MPU6500 có được kết nối không
  if (!mpu.testConnection()) {
    Serial.println("MPU6500 is not connected!");
    while (1);
  }

  programSelector.add(new AcceGyroProgram(&acceGyroRenderer));
  programSelector.add(new JumpingDemoProgram(&detector));

  programSelector.begin();
}

void loop() {
  mpu.getAcceleration(&ax, &ay, &az);
  detector.update(ax, ay, az);

  programSelector.check();

  delay(60);
}
