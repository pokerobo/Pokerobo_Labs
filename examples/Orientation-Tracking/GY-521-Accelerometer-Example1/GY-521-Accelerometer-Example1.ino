#include <Wire.h>

#define FULL_SCALE_RANGE_SUPPORT      1
#define DEBUG_ENABLED                 0

const int MPU = 0x68; // MPU6050 I2C address

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
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission

  #if FULL_SCALE_RANGE_SUPPORT
  // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
  Wire.write(0x10);                  //Set the register bits as 00010000 (+/- 8g full scale range)
  Wire.endTransmission(true);
  // Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
  Wire.write(0x10);                   // Set the register bits as 00010000 (1000deg/s full scale)
  Wire.endTransmission(true);
  #endif
}

void AcceGyroReader::read() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers

  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value

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
