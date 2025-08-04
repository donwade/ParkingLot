// #https://docs.m5stack.com/en/arduino/m5station/rgb#example
// Station RGB LED example program.This program is based on Adafruit NeoPixel library,
// please install Adafruit NeoPixel dependency library through the library manager before use.

#include <M5Unified.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN    4
#define NUM_LEDS   7

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.setTextDatum(middle_center);
  M5.Display.setTextFont(&fonts::Orbitron_Light_24);
  M5.Display.setTextSize(1);
  M5.Display.drawString("RGB LED Test", M5.Display.width() / 2, M5.Display.height() / 2);
  strip.begin();
  strip.show();
}

void loop() {
    //RED
    for(char i = 0; i <= NUM_LEDS; i++)
    {strip.setPixelColor(i, strip.Color(255, 0, 0)); }
    strip.show();
    delay(1000);

    //GREEN
    for(char i = 0; i <= NUM_LEDS; i++)
    {strip.setPixelColor(i, strip.Color(0, 255, 0)); }
    strip.show();
    delay(1000);

    //BLUE
    for(char i = 0; i <= NUM_LEDS; i++)
    {strip.setPixelColor(i, strip.Color(0, 0, 255)); }
    strip.show();
    delay(1000);
}

