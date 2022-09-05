#include "switch_variables.h"
void setup_sw_led () {
    // set pin
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    // generate, save and display led colors
    randomSeed(analogRead(0));
    int r;
    for (int i = 0; i < 6; i++) { 
        r = random(4);
        // si on obtient nombre paire (0 ou 2) c'est soit vert, soit blanc donc il faut que le switch soit en bas
        if(r%2 == 0) {
            sw_mvt[i] = 0;
        }

        for (int j = 0; j < 3; j++) {
            led_color[i][j] = color[r][j];
        }
        //Serial.print(led_color[i]);
        strip.setPixelColor(i, led_color[i][0], led_color[i][1], led_color[i][2]);
    }

    // setup the switches
    // get the switches position
    for (int i = 0; i < 6; i++) {
        sw_position[i] = digitalRead(i);
    }

    strip.setBrightness(10);
    strip.show();
}


int switch_game() {
    // setup the leds and switches
    setup_sw_led();

    // save switch movement 6 tries one/switch
    int mvt_counter = 0;
    int check = 0;
    while (mvt_counter != 6 || check == 6) {
        for (int i = 0; i < 6; i++) {
            if(digitalRead(i) != sw_position[i]) {
                mvt_counter ++;
                if(digitalRead(i) %2 == sw_position[i])
                    check++;
            }
        }
    }
    if (check == 6)
        return 1;

    return 0;
}