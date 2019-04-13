#pragma once

#include <Arduino.h>
#include <CmdMessenger.h>

enum Commands {
  kAcknowledge,
  kError,
  kStatus,
  kGPS,
  kOrientation,
  kCalibration,
  kServo,
  kInnerLight,
  kOuterLight
};

static CmdMessenger messenger(Serial);
