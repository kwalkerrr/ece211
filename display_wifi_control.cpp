#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <Fonts/FreeSans12pt7b.h>
#include "neopixel_control.h"
#include "config.h"
#include "display_wifi_control.h"

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

static Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);

static const unsigned long update_interval = 60000;
static unsigned long last_update = 0;

void display_wifi_init() {
  static bool called = false;
  if (called) {
    Serial.println("display_wifi_init: function cannot be called more than once");
    return;
  }
  
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(GC9A01A_BLACK);
  tft.setTextColor(GC9A01A_CYAN);

  tft.setTextSize(2);
  tft.setCursor(45, 110);
  tft.print("Connecting...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  tft.fillScreen(GC9A01A_BLACK);

  last_update = millis();

  called = true;
}

bool display_wifi_check_update() {
  if (millis() - last_update >= update_interval) {
    last_update = millis();
    return true;
  }
  else {
    return false;
  }
}

static void drawTemperature(float temperature_fahrenheit) {

  tft.fillRect(35, 85, 170, 70, GC9A01A_BLACK);

  tft.setTextColor(GC9A01A_GREEN);
  tft.setTextSize(2);
  tft.setCursor(48, 70);
  tft.print("Portland, OR");

  tft.setTextColor(GC9A01A_WHITE);
  tft.setTextSize(6);
  tft.setCursor(31, 105);
  tft.print(temperature_fahrenheit, 1);

  int cursorX = tft.getCursorX();
  tft.drawCircle(cursorX + 6, 108, 4, GC9A01A_WHITE);
  tft.setCursor(cursorX + 14, 105);
  tft.print("F");
}

void display_wifi_get_show_temp() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
    return;
  }

  HTTPClient http;
  
  String url = "https://api.open-meteo.com/v1/forecast?latitude=45.5234&longitude=-122.6762&hourly=temperature_2m&current=temperature_2m&temperature_unit=fahrenheit";

  http.begin(url);
  int http_response_code = http.GET();

  if (http_response_code == 200) {
    String payload = http.getString();

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);

    if (!error) {
      float temperature_fahrenheit = doc["current"]["temperature_2m"];
      drawTemperature(temperature_fahrenheit);
    }
  } else {
    tft.fillRect(40, 95, 160, 50, GC9A01A_BLACK);
    tft.setTextColor(GC9A01A_RED);
    tft.setTextSize(2);
    tft.setCursor(65, 110);
    tft.print("API Error");
  }

  http.end();
}

static condition_t weather_code_to_condition(int code) {
  switch (code) {
    case 0: case 1:
      return CLEAR;
    case 2: case 3:
      return CLOUDY;
    case 45: case 48:
      return FOG;
    case 51: case 53: case 55:
    case 61: case 63: case 65:
    case 80: case 81: case 82:
      return RAIN;
    case 56: case 57:
    case 66: case 67:
      return FREEZING_RAIN;
    case 71: case 73: case 75: case 77:
    case 85: case 86:
      return SNOW;
    case 95: case 96: case 97: case 99:
      return THUNDERSTORM;
    default:
      return INVALID;
  }
}

condition_t display_wifi_get_condition() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
    return INVALID;
  }

  HTTPClient http;
  
  String url = "https://api.open-meteo.com/v1/forecast?latitude=45.5234&longitude=-122.6762&current=weather_code";

  int weather_code = -1;

  http.begin(url);
  int http_response_code = http.GET();

  if (http_response_code == 200) {
    String payload = http.getString();

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);

    if (!error) {
      weather_code = doc["current"]["weather_code"] | -1;
    }
  }
  else {
    tft.fillRect(40, 95, 160, 50, GC9A01A_BLACK);
    tft.setTextColor(GC9A01A_RED);
    tft.setTextSize(2);
    tft.setCursor(65, 110);
    tft.print("API Error");
  }

  http.end();
  return weather_code_to_condition(weather_code);
}
