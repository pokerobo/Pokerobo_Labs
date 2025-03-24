#include <Arduino.h>

// chân analog kết nối tới cảm biến LM35
int sensorPin = A2;

void setup() {
  // Khởi động Serial ở mức baudrate 57600
  Serial.begin(57600);
  analogReference(INTERNAL);
  // Bạn không cần phải pinMode cho các chân analog trước khi dùng nó
}
 
void loop() {
  // đọc giá trị từ cảm biến LM35
  float reading = analogRead(sensorPin);  

  // tính ra giá trị hiệu điện thế (đơn vị Volt) từ giá trị cảm biến
  float milliVolt = reading * 5000.0 / 1023.0; 

  // trong cảm biến LM35, mỗi 10mV = 1 độ C.
  // Vì vậy, khi biến voltage là biến lưu hiệu điện thế (đơn vị Volt)
  // thì ta chỉ việc nhân voltage cho 100 là ra được nhiệt độ!
  float temp = milliVolt / 10;

  Serial.print("Temperature = ");
  Serial.println(temp);

  // đợi 1 giây cho lần đọc tiếp theo
  delay(1000);
}
