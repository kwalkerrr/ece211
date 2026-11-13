# Required Libraries
This code requires the following libraries. They should each be installed using
the Ardunio IDE directly by going to Library Manager (bookshelf icon on the
left) and then searching for the exact names listed here.
- Adafruit IO Arduino
- Adafruit MQTT Library
- Adafruit NeoPixel
- Any libraries needed for the display
Additionally, you need to create your own config.h file in the same directory as
ece211_practicum.ino. A template is provided below.
```cpp
#pragma once

#include <AdafruitIO_WiFi.h>

#define IO_USERNAME "adafruitiousername"
#define IO_KEY "adafruitiokey"
#define WIFI_SSID "wifiname"
#define WIFI_PASS "wifipassword"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
```
