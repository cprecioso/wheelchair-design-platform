#include "Orientation.h"

namespace Orientation {
// Create Adafruit BNO
Adafruit_BNO055 bno = Adafruit_BNO055(55);

// Initializes BNO055 sensor
void setup(void) {
  if (!bno.begin()) {
    while (true)
      ;
  }
  delay(1000);
  bno.setExtCrystalUse(true);
}

bool isCalibrated() {
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t sys, gyro, accel, mag;  // variable for gyroscope, accelerometer
                                  // and magnetometer
  sys = gyro = accel = mag = 0;
  bno.getCalibration(&sys, &gyro, &accel, &mag);

  // Command is sent when \n (\r) or println is called
  // AT+GATTCHAR=CharacteristicID,value
  messenger.sendCmdStart(kCalibration);
  messenger.sendCmdArg(sys);
  messenger.sendCmdArg(gyro);
  messenger.sendCmdArg(accel);
  messenger.sendCmdArg(mag);
  messenger.sendCmdEnd();

  if (gyro >= 2) {
    return true;
  } else {
    return false;
  }
}

void loop() {
  static auto lastTime = millis();
  if (millis() - lastTime < 1000) return;
  lastTime = millis();

  if (!isCalibrated()) {
    return;
  }

  sensors_event_t event;
  bno.getEvent(&event);

  messenger.sendCmdStart(kOrientation);
  messenger.sendCmdArg(event.orientation.x);
  messenger.sendCmdArg(event.orientation.y);
  messenger.sendCmdArg(event.orientation.z);
  messenger.sendCmdEnd();
}
}  // namespace Orientation
