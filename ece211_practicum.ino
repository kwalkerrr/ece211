#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <AdafruitIO.h>
#include "config.h" // must create yourself
#include <Wire.h> // if I2C is needed for display communication
// include any other display libraries here

// team-created modules
#include "neopixel_control.h"

#define BAUD_RATE 115200

void setup() {
  Serial.begin(BAUD_RATE);
  neopixel_begin();
}

void loop() {
  neopixel_clear_all();
  neopixel_light(OFF, 0, 12);
  delay(1000);
  neopixel_clear_all();
  neopixel_light(YELLOW, 0, 12);
  delay(1000);
  neopixel_clear_all();
  neopixel_light(LIGHT_BLUE, 0, 12);
  delay(1000);
  neopixel_clear_all();
  neopixel_light(GRAY, 0, 12);
  delay(1000);
}
