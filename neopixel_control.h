#pragma once

#include <stdint.h>

enum color_t {
  OFF,
  YELLOW,
  LIGHT_BLUE,
  GRAY
};

/*
Initializes the NeoPixel LEDs. This function should only
be called once.
*/
void neopixel_begin();

/*
Sets the RGBW bits for all of the LEDs in the strip to 0,
but does not call show() (i.e. this function does not
make the strip LEDs actually turn off by itself).
*/
void neopixel_clear_all();

/*
Lights up the specified LEDs with the specified color.
LEDs are 0-indexed.
*/
void neopixel_light(color_t color, uint8_t first_led, uint8_t count);