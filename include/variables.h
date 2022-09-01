#include <time.h>
#include <stdlib.h>
#include <Adafruit_NeoPixel.h>


    /* switch game */
// Leds
#define LED_PIN    4
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 6
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int led_color[6][3];
// white, red, green, blue
int color[4][4] = {
                    {255, 255, 255},
                    {255, 0, 0},
                    {0, 255, 0},
                    {0, 0, 255}};

// Switches
int sw_mvt[6];
int sw_position[6];

