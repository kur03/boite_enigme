#include "word_variables.h"

void setup_screen() {
    lcd.begin(16, 2);
}

int get_joystick_value(int i, int j) {
    if (xValue == 0 && yValue == 511)
        return 1; //  we go left
    else if (xValue == 1023 && yValue == 511)
        return 2; //  we go right

    else if (xValue == 511 && yValue == 1023)
        return 3; //  we go up;
    else if (xValue == 511 && yValue == 0)
        return 4; //  we go down
    else
        return 5;
}

/*int check (char *answer, char *game) {
    for (int i = 0; i < sizeof(answer); i++) {
        if (answer[i] != game[i])
            return 0;
    }
    return 1;
}*/

int word_game () {
    setup_screen();

    //  i for up&down and j for left&right
    int r, i = 0, j = 1, mvt;
    char *answer, *game;
    
    // randomly choose a word
    randomSeed(analogRead(0));
    r = random(4) + 1;
    
    switch(r) {
        case 1:
            //  dtre
            answer = dtre;
            break;
        case 2:
            //  gperdu
            answer = gperdu;
            break;
        case 3:
            //  cfdr;
            answer = cfdr;
            break;
        case 4:
            //  poppy
            answer = poppy;
            break;
    }

    for (int i = 0; i < int(sizeof(answer)); i++) {
        game[i] = 'A';
    }
    lcd.setCursor(0, 1);

    // play
    while (game != answer) {
        //  read joystick value
        xValue = analogRead(joyX);
        yValue = analogRead(joyY);
        mvt = get_joystick_value(i, j);

        switch (mvt)
        {
            case 1:
                // print new letter and change saved letter
                lcd.print(alphabet[i+1]);
                game[i] = alphabet[i+1];
                break;

            case 2:
                // print new letter and change saved letter
                lcd.print(alphabet[i-1]);
                game[i] = alphabet[i-1];
                break;

            case 3:
                // place cursor
                lcd.setCursor(j-1, 1);
                break;

            case 4:
                // place cursor
                lcd.setCursor(j+1, 1);
                break;

            default :
                lcd.setCursor(j, 1);
                break;
        }
    }
    return 1;
}