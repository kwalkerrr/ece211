#include "neopixel_control.h"
#include "display_wifi_control.h"

#define BAUD_RATE 115200

static void update_all();
static void update_condition_leds(condition_t condition);

void setup() {
  Serial.begin(BAUD_RATE);
  neopixel_init();
  display_wifi_init();
  update_all();
}

void loop() {
  if (display_wifi_check_update()) {
    update_all();
  }
  else {
    delay(1000);
  }
}

static void update_all() {
  display_wifi_get_show_temp();
  condition_t condition = display_wifi_get_condition();
  update_condition_leds(condition);
}

static void update_condition_leds(condition_t condition) {
  switch (condition) {
    case INVALID:
      return;
    case CLEAR:
      neopixel_clear_all();
      neopixel_light(YELLOW, 0, NEOPIXEL_COUNT);
      break;
    case CLOUDY:
      neopixel_clear_all();
      neopixel_light(GRAY, 0, NEOPIXEL_COUNT);
      break;
    case FOG:
      neopixel_clear_all();
      neopixel_light(GRAY, 0, NEOPIXEL_COUNT);
      break;
    case RAIN:
      neopixel_clear_all();
      neopixel_light(DARK_BLUE, 0, NEOPIXEL_COUNT);
      break;
    case FREEZING_RAIN:
      neopixel_clear_all();
      neopixel_light(LIGHT_BLUE, 0, NEOPIXEL_COUNT);
      break;
    case SNOW:
      neopixel_clear_all();
      neopixel_light(WHITE, 0, NEOPIXEL_COUNT);
      break;
    case THUNDERSTORM:
      neopixel_clear_all();
      neopixel_light(GRAY, 0, NEOPIXEL_COUNT);
      break;
  }
}