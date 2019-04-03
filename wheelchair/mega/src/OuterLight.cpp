#include "OuterLight.h"

namespace OuterLight {
const auto pin = 7;
const auto numPixels = 16;

CRGBArray<numPixels> leds;

const auto low = CRGB(0, 0, 0);
const auto mid = CRGB(0, 0, 10);
const auto high = CRGB(60, 60, 100);

void setup() {
  FastLED.addLeds<NEOPIXEL, pin>(leds, numPixels);
  FastLED.show();
}

void setDirection(byte direction) {
  leds.fill_solid(low);

  byte ledNumber = direction * 4;

  leds[ledNumber + 1] = high;
  leds[ledNumber] = mid;
  leds[ledNumber + 2] = mid;

  FastLED.show();
}
}  // namespace OuterLight
