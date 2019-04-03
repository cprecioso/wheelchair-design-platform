#pragma once

#include <Arduino.h>
#include <FastLED.h>

#include "Messenger.h"

namespace InnerLight {
void setup();

void setColor(byte, byte, byte);
}  // namespace InnerLight
