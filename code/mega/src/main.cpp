#include <Arduino.h>

#include "Messenger.h"
#include "GPS.h"
#include "Orientation.h"
#include "ServoMotor.h"
#include "InnerLight.h"
#include "OuterLight.h"

void setup(void) {
  delay(500);

  Serial.begin(115200);
  messenger.printLfCr();
  messenger.sendCmd(kStatus, "Start!");

  // Setup sensors
  Orientation::setup();
  GPS::setup();

  // Setup each actuator and the command the will be responding to
  ServoMotor::setup();
  messenger.attach(kServo, [] {
    const auto angle = messenger.readInt16Arg();
    ServoMotor::setAngle(angle);
  });

  InnerLight::setup();
  messenger.attach(kInnerLight, [] {
    const byte r = messenger.readInt16Arg();
    const byte g = messenger.readInt16Arg();
    const byte b = messenger.readInt16Arg();
    InnerLight::setColor(r, g, b);
    messenger.sendCmd(kStatus, F("Set!"));
    messenger.sendCmd(kStatus, r);
    messenger.sendCmd(kStatus, g);
    messenger.sendCmd(kStatus, b);
  });

  OuterLight::setup();
  messenger.attach(kOuterLight, [] {
    const byte direction = messenger.readInt16Arg();
    OuterLight::setDirection(direction);
  });

  messenger.attach([] { messenger.sendCmd(kError, F("Unknown command")); });

  messenger.sendCmd(kStatus, "Ready!");
}

void loop(void) {
  messenger.feedinSerialData();

  Orientation::loop();
  GPS::loop();
}
