#include <Wire.h>

// MPU6050 I2C address
const int MPU_ADDR = 0x68; 

int16_t ax, ay, az, gx, gy, gz, temp;
void setup() {
  Serial.begin(115200);
  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();
  delay(1000); // Give the sensor time to stabilize

  // Wake up the MPU-6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // Power Management 1 register
  Wire.write(0);    // Set to 0 to wake it up
  if (Wire.endTransmission() != 0) {
    Serial.println("Wake up failed! Check wires.");
  } else {
    Serial.println("Sensor Woken Up!");
  }

  // Set Accelerometer Sensitivity (Optional but recommended)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1C); // Accel Config
  Wire.write(0);    // Set to +/- 2g
  Wire.endTransmission();
}
void loop() {
  // Request 14 bytes starting from register 0x3B
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  // Read data
  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();
  temp = Wire.read() << 8 | Wire.read();
  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();

  // Print for Serial Plotter/Monitor
  Serial.print("AccX:"); Serial.print(ax);
  Serial.print(",AccY:"); Serial.print(ay);
  Serial.print(",AccZ:"); Serial.print(az);
  Serial.print(",GyrX:"); Serial.print(gx);
  Serial.print(",GyrY:"); Serial.print(gy);
  Serial.print(",GyrZ:"); Serial.println(gz);

  delay(50); 
}