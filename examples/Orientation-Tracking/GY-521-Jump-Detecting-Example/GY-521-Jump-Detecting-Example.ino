#include <Wire.h>
#include <MPU6050.h>

#include "Pokerobo_Lab_MPU_JumpingDetector.h"

#if defined(ARDUINO_UNOR4_WIFI)
#include "Pokerobo_Lab_MPU_EventToKeyboard.h"
#endif

GeometryDisplayHandler displayHandler;
AcceGyroRenderer acceGyroRenderer(&displayHandler);
JumpingListener eventListener;
JumpingDetectorDebug detector(&eventListener,
    &displayHandler,
    &acceGyroRenderer);

MPU6050 mpu;

int16_t ax, ay, az;  // Gia tốc trên các trục
int16_t gx, gy, gz;  // Góc quay trên các trục

void setup() {
  // Khởi tạo giao tiếp I2C
  Wire.begin();
  Serial.begin(57600);
  displayHandler.begin();

  // Khởi tạo MPU6500
  mpu.initialize();
  
  // Kiểm tra xem MPU6500 có được kết nối không
  if (!mpu.testConnection()) {
    Serial.println("MPU6500 is not connected!");
    while (1);
  }
}

void loop() {
  mpu.getAcceleration(&ax, &ay, &az);
  detector.update(ax, ay, az);
  detector.render();

  delay(40);
}
