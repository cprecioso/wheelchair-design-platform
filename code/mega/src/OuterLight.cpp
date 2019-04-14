#include "OuterLight.h"

namespace OuterLight {
const auto pin = 7;
const auto numPixels = 16;

CRGBArray<numPixels> leds;

const auto low = CRGB(0, 0, 0);
const auto mid = CRGB(0, 0, 100);
const auto high = CRGB(0, 0, 255);

void setup() {
  FastLED.addLeds<NEOPIXEL, pin>(leds, numPixels);
  leds.fill_solid(low);
  FastLED.show();
}

void setDirection(byte direction) {
  // We want to show the direction with a main bright LED and the two adjacent
  // ones being less bright, for a more aesthetic effect. e.g. turn left:
  //
  //      *  *  *  *
  //     o          *
  //     O          *
  //     o          *
  //     *          *
  //      *  *  *  *
  //
  // To do that, we get a direction 0,1,2,3 and multiply by four, so we will
  // onlt get a "central" LED every four positions. Then we set that one at
  // maximum brightness and the two immediately adjacent to middle brightness.

  leds.fill_solid(low);

  byte ledNumber = direction * 4;

  leds[ledNumber + 1] = high;
  leds[ledNumber] = mid;
  leds[ledNumber + 2] = mid;

  FastLED.show();
}
}  // namespace OuterLight
