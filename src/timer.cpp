#include "timer_variables.h"


void change_color(int counter, int color, int mvt) {
    // on décide si on va vers la gauche ou la droite
    int sens = random(1,2);
    while(mvt != 0) {
        led_color[counter] = color;
        // on allume les leds en fonction
        strip.setPixelColor(counter, color, 0, 0);
        // we go right we increment
        if (sens == 1)
            counter ++;
        // we go left we decrement
        else
            counter --;
        mvt--;
    }
}

int led_timer(int counter) {
    // on set les leds
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    // generate, save and display led colors
    
    // on génère un nombre en 1 et 3
    randomSeed(analogRead(0));
    int r, sens;
    r = random(1, 3);
    sens = random(1,2);
    // if the current led is off i turn it on
        if(led_color[counter] == 0) 
            change_color(counter, 255, r);
        
    // if the current led is off i turn it off
        else if(led_color[counter] == 255)
            change_color(counter, 0, r);
    
    // we reach the lower half (zero if the went by the left and 16 by the right)
    if (counter == (0 || 16))
        return 1;
    

    strip.setBrightness(10);
    strip.show();
    
    
    return 0;
}