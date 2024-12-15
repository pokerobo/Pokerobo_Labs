#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

#define FULL_SCALE_RANGE_SUPPORT      1
#define DEBUG_ENABLED                 0

class AcceGyroReader {
  public:
    void begin();
    void read();
    float getRoll();
    float getPitch();
    void debug();
  private:
    float AccX, AccY, AccZ;
    float accAngleX, accAngleY;
    float roll, pitch;
};

void AcceGyroReader::begin() {
  mpu.begin();
  delay(10);

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(10);
}

void AcceGyroReader::read() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = a.acceleration.x / 10.0; // X-axis value
  AccY = a.acceleration.y / 10.0; // Y-axis value
  AccZ = a.acceleration.z / 10.0; // Z-axis value

  // swaping the value of AccX with AccY
  float AccX_ = AccY, AccY_ = -AccX, AccZ_ = AccZ;

  // Calculating Roll and Pitch from the accelerometer data
  accAngleX = (atan(AccY_ / sqrt(pow(AccX_, 2) + pow(AccZ_, 2))) * 180 / PI);
  accAngleY = (atan(-1 * AccX_ / sqrt(pow(AccY_, 2) + pow(AccZ_, 2))) * 180 / PI);

  roll = accAngleX;
  pitch = accAngleY;
}

void AcceGyroReader::debug() {
  Serial.print("Acceleration X: ");
  Serial.print(AccX);
  Serial.print(", Y: ");
  Serial.print(AccY);
  Serial.print(", Z: ");
  Serial.print(AccZ);
  Serial.println(" m/s^2");

  Serial.println("");
  delay(500);
}

float AcceGyroReader::getRoll() {
  return roll;
}

float AcceGyroReader::getPitch() {
  return pitch;
}

AcceGyroReader reader;

void setup() {
  Serial.begin(57600);
  reader.begin();
}

void loop() {
  reader.read();
  
  #if DEBUG_ENABLED
  reader.debug();
  #else
  Serial.print(reader.getRoll());
  Serial.print("/");
  Serial.print(reader.getPitch());
  Serial.println();
  delay(100);
  #endif
}
