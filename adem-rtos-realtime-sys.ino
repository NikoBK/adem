#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LEDS_COUNT  1 // Just one LED
#define LEDS_PIN	8 // Pin 8 for CPIO8
#define CHANNEL		0

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

int delayMS = 2000;

void setup() {
	strip.begin();
	strip.setBrightness(3);	
}

void loop() {
	  strip.setLedColorData(0, 255, 255, 255);
    strip.show();
    delay(delayMS);
    strip.setLedColorData(0, 0, 0, 0);
    strip.show();
    delay(delayMS);
}