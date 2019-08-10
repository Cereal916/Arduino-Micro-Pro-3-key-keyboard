#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <time.h>

/*
 * SunFounder 0.96" Inch Blue I2C IIC Serial 128x64 OLED LCD LED SSD1306 Module for Arduino Raspberry Pi Display
 * https://smile.amazon.com/gp/product/B014KUB1SA/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1
 * Simply prints out a random number
 */
// SunFounder 0.96" Inch Blue I2C IIC Serial 128x64 OLED LCD LED SSD1306 Module for Arduino Raspberry Pi Display
// https://smile.amazon.com/gp/product/B014KUB1SA/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1



// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#endif

#include "Keyboard.h"

const int buttonPin[] = {2, 3, 4, 5};
int pinCount = 4;
int buttonState[] = {0, 0, 0, 0};
int prevButtonState[] = {HIGH, HIGH, HIGH};

long lastDebounceTime[] = {0, 0, 0, 0};
long debounceDelay = 50;
void setup() {
    srand(time(0));
    int choice = rand();
    // initialize and clear display
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.clearDisplay();
    display.display();


    for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {
        pinMode(buttonPin[thisPin], INPUT);
        digitalWrite(buttonPin[thisPin], HIGH);
    }

    Keyboard.begin();
}

// Output actions. Probably the only part that you need to change
int outputAction(int currentButton) {
    if (currentButton == 2) {
        int choice = rand();
        display.clearDisplay();
        display.setTextSize(3);
        display.setTextColor(WHITE);
        display.setCursor(10,5);
        display.print(choice);
        display.display();
    }
}
void loop() {
    for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {
        buttonState[thisPin] = digitalRead(buttonPin[thisPin]);

        if ((buttonState[thisPin] != prevButtonState[thisPin]) && (buttonState[thisPin] == HIGH)) {
            if ((millis() - lastDebounceTime[thisPin]) > debounceDelay) {
                outputAction(thisPin);
                lastDebounceTime[thisPin] = millis();
            }
        }

        prevButtonState[thisPin] = buttonState[thisPin];
    }
}