#include <Arduino.h>
#include <LiquidCrystal.h>

   /* Word game */
// screen pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//  joystick pins
#define joyX A0
#define joyY A1
int xValue = 0;
int yValue = 0;

//  words
char dtre[4] = {'D', 'T', 'R', 'E'};
char gperdu[6] = {'G', 'P', 'E', 'R', 'D', 'U'};
char cfdr[4] = {'C', 'D', 'F', 'R'};
char poppy[5] = {'P', 'O', 'P', 'P', 'Y'};
char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
