#pragma once

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <Fonts/FreeSans12pt7b.h>

enum condition_t {
  INVALID,
  CLEAR,
  CLOUDY,
  FOG,
  RAIN,
  FREEZING_RAIN,
  SNOW,
  THUNDERSTORM
};

void display_wifi_init();

bool display_wifi_check_update();

void display_wifi_get_show_temp();

condition_t display_wifi_get_condition();
