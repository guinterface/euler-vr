#include <Wire.h>
#include <MPU6050.h>

MPU6050 imu;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  imu.initialize();

  if (!imu.testConnection()) {
    Serial.println("IMU connection failed!");
    while (1);
  }
  Serial.println("IMU ready");
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw gyro data to degrees/sec (adjust sensitivity as needed)
  float pitch = gx / 131.0;
  float roll  = gy / 131.0;
  float yaw   = gz / 131.0;

  // Send yaw/pitch/roll via serial
  Serial.print("YPR:");
  Serial.print(yaw); Serial.print(",");
  Serial.print(pitch); Serial.print(",");
  Serial.println(roll);

  delay(10); // 100 Hz update rate
}
