#include "InnerLight.h"

namespace InnerLight {
const auto pin = 6;
const auto numPixels = 12;

CRGBArray<numPixels> leds;

void setup() {
  FastLED.addLeds<NEOPIXEL, pin>(leds, numPixels);
  FastLED.show();
}

void setColor(byte r, byte g, byte b) {
  leds.fill_solid(CRGB(r, g, b));
  FastLED.show();
}
}  // namespace InnerLight
