#include "neopixel_control.h"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

#define NEOPIXEL_PIN 23
#define NEOPIXEL_COUNT 12
#define NEOPIXEL_BRIGHTNESS 50

static Adafruit_NeoPixel strip(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRBW + NEO_KHZ800);

void neopixel_begin() {
  static bool called = false;
  if (called) {
    Serial.println("neopixel_begin: function cannot be called more than once");
    return;
  }
  strip.begin();
  strip.show();
  strip.setBrightness(NEOPIXEL_BRIGHTNESS);
  called = true;
}

void neopixel_clear_all() {
  strip.fill(strip.Color(0, 0, 0, 0), 0, strip.numPixels());
}

void neopixel_light(color_t color, uint8_t first_led, uint8_t count) {
  if (first_led < 0 || first_led > strip.numPixels() - 1) {
    Serial.println("neopixel_light: first_led must be between 0 and NEOPIXEL_COUNT - 1");
    return;
  }
  else if (first_led + count > strip.numPixels()) {
    Serial.println("neopixel_light: first_led + count must be <= NEOPIXEL_COUNT");
    return;
  }
  
  switch (color) {
    case OFF:
      strip.fill(strip.Color(0, 0, 0, 0), first_led, count);
      break;
    case YELLOW:
      strip.fill(strip.Color(255, 125, 0, 10), first_led, count);
      break;
    case LIGHT_BLUE:
      strip.fill(strip.Color(25, 50, 230, 10), first_led, count);
      break;
    case GRAY:
      strip.fill(strip.Color(13, 13, 13, 20), first_led, count);
      break;
  }
  strip.show();
}