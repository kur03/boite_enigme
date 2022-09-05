#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

    /* switch game */
// Leds
#define LED_PIN    5
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 16
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// the led in the middle is turned on
int led_color[LED_COUNT] = {0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0};
// white, red, green, blue
int color[4][4] = {
                    {255, 255, 255},
                    {255, 0, 0},
                    {0, 255, 0},
                    {0, 0, 255}};