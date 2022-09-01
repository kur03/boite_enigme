#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include <BCDDecoderDriver74LS47.h>

#define pinA 4
#define pinB 5
#define pinC 6
#define pinD 7

#define pinRBI 9

BCDDecoderDriver74LS47 sevenSegDisplay(pinA, pinB, pinC, pinD, pinRBI);

unsigned long countdownStart = 0;         // countdown start in ms, used to offset countdown
unsigned long countdownDuration = 300000; // countdown duration in ms (5 minutes)

#define seven_seg_count 4
char seven_seg_en[seven_seg_count] = {2, 3, 10, 11}; //seven segment pin definition
char seven_seg_char[seven_seg_count] = {0,0,0,0}; //shared from timer to 7 seg display

// returns coutdown since start in ms
// countdown stops at 0
unsigned long getCountDown()
{
    unsigned long currentTime = xTaskGetTickCount();
    unsigned long deadline = (countdownDuration + countdownStart) / portTICK_PERIOD_MS;

    if (currentTime > deadline)
    {
        // countdown reached, return 0;
        return 0;
    }
    // countdown ongoing, return time left
    return (deadline - currentTime) * portTICK_PERIOD_MS;
}

// define two tasks for Blink & AnalogRead
void TaskSevenSeg(void *pvParameters);
void TaskTimer(void *pvParameters);
void TaskAnalogRead(void *pvParameters);

// the setup function runs once when you press reset or power the board
void setup()
{

    sevenSegDisplay.display(true);

    // iterate over every display
    for (int i = 0; i < seven_seg_count; i++)
    {
        pinMode(seven_seg_en[i], OUTPUT);
        digitalWrite(seven_seg_en[i], HIGH);
    }

    // initialize serial communication at 9600 bits per second:
    Serial.begin(115200);

    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
    }
    Serial.print("Serial intialized. creating tasks...");

    // Now set up two tasks to run independently.
    xTaskCreate(
        TaskSevenSeg, "TaskSevenSeg" // A name just for humans
        ,
        1024 // This stack size can be checked & adjusted by reading the Stack Highwater
        ,
        NULL, 3 // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        ,
        NULL);

    xTaskCreate(
        TaskTimer, "TaskTimer" // A name just for humans
        ,
        1024 // This stack size can be checked & adjusted by reading the Stack Highwater
        ,
        NULL, 2 // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        ,
        NULL);



    // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
    // Serial.print("starting scheduler");
    // vTaskStartScheduler();
    // Serial.print("insufficient ram!");
}

void loop()
{
    // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskAnalogRead(void *pvParameters) // This is a task.
{
    (void)pvParameters;


        vTaskDelay(1000 / portTICK_PERIOD_MS);
        Serial.print("kek");
    for(;;)
    {
    }

}

void TaskMaster(void *pvParameters)
{
    (void)pvParameters;
}

char getdigit(unsigned long number, unsigned short nth_digit)
{
    while (nth_digit--)
    {
        number /= 10;
    }
    return (number % 10) + '0';
}


void TaskTimer(void *pvParameters) // continually updates the 7segment display
{
    (void)pvParameters;

    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        unsigned long time_left_cs = getCountDown() / 10; // centiseconds
        unsigned long time_left_s = time_left_cs / 100;   // seconds
        unsigned long time_left_m = time_left_s / 60;     // minutes

        unsigned long time_left_ss = time_left_s % 60;   // seconds mod 60
        unsigned long time_left_mm = time_left_m % 60;     // minutes mod 60

        // if over a minute is left, display mm:ss
        if (time_left_s > 60)
        {
            seven_seg_char[0] = getdigit(time_left_ss, 0); // seconds
            seven_seg_char[1] = getdigit(time_left_ss, 1); // tens of seconds
            seven_seg_char[2] = getdigit(time_left_mm, 0); // minutes
            seven_seg_char[3] = getdigit(time_left_mm, 1); // tens of minutes
        }
        else // if under a minute is left, diplay ss:cs
        {
            seven_seg_char[0] = getdigit(time_left_cs, 0); // centiseconds
            seven_seg_char[1] = getdigit(time_left_cs, 1); // tens of centiseconds
            seven_seg_char[2] = getdigit(time_left_ss, 0);  // seconds
            seven_seg_char[3] = getdigit(time_left_ss, 1);  // tens of seconds
        }

        Serial.print("Task1 : ");
        Serial.print(seven_seg_char[3]);
        Serial.print(seven_seg_char[2]);
        Serial.print(":");
        Serial.print(seven_seg_char[1]);
        Serial.println(seven_seg_char[0]);
    }
}

void TaskSevenSeg(void *pvParameters) // continually updates the 7segment display
{
    (void)pvParameters;

    while (1)
    {
        for(int i = 0; i < seven_seg_count; i++)
        {
            digitalWrite(seven_seg_en[i], LOW);
            sevenSegDisplay.setNumber(seven_seg_char[0]);
            digitalWrite(seven_seg_en[i], HIGH);
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
    }
}

