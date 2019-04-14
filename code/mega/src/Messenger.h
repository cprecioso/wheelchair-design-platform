#pragma once

#include <Arduino.h>
#include <CmdMessenger.h>

enum Commands {
  kAcknowledge,  // Required for CmdMessenger library
  kError,        // Not really used, nice to have just in case
  kStatus,       // General messages, mostly used for debug
  kGPS,          // GPS sensor processed data
  kOrientation,  // Orientation sensor data
  kCalibration,  // Calibration data of the orientation sensor
  kServo,        // Command to move servo
  kInnerLight,   // Command to control 12-LED ring
  kOuterLight    // Command to control 16-LED ring
};

static CmdMessenger messenger(Serial);
