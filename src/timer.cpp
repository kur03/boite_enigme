#include "timer_variables.h"
void setup_led () {
    // set pin
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    // generate, save and display led colors
    randomSeed(analogRead(0));
    int r;
    for (int i = 0; i < 6; i++) { 
        r = random(2, 3);
        // si on obtient nombre paire (0 ou 2) c'est soit vert, soit blanc donc il faut que le switch soit en bas

        for (int j = 0; j < 3; j++) {
            led_color[i][j] = color[r][j];
        }
        //Serial.print(led_color[i]);
        strip.setPixelColor(i, led_color[i][0], led_color[i][1], led_color[i][2]);
    }

    strip.setBrightness(10);
    strip.show();
}

int led_timer() {
    setup_led();
    
    return 1;
}