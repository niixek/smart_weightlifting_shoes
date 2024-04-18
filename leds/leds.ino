#include <FastLED.h>
#include <string.h>

#define LED_PIN     6
#define NUM_LEDS    12

CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.clear(); // Clear all LEDs
    FastLED.show();  // Make sure to call show() to update the LEDs
}

void lightHelper(char* dir) {

    int start, end;
    CRGB color;

    start = 0;
    end = NUM_LEDS;
    color = CRGB(0, 200, 0);

    FastLED.clear();
    
    if (!strcmp(dir,"forward")) {
        start = 0;
        end = start + NUM_LEDS / 4;
        color = CRGB(200, 0, 0);
    } 

    if (!strcmp(dir, "backward")) {
        start = NUM_LEDS / 4;
        end = start + NUM_LEDS / 4;
        color = CRGB(200, 0, 0);
    } 

    if (!strcmp(dir, "right")) {
        start = 2 * (NUM_LEDS / 4);
        end = start + NUM_LEDS / 4;
        color = CRGB(200, 0, 0);
    } 

    if (!strcmp(dir, "left")) {
        start = 3 * (NUM_LEDS / 4);
        end = start + NUM_LEDS / 4;
        color = CRGB(200, 0, 0);
    } 

    for (int i = start; i < end; i++) {
        leds[i] = color;
    }

    FastLED.show(); // Show the updated LED colors
}

/*
void loop(){
    for (int i = 0; i < 2; i++) {
        leds[i] = CRGB(0, 0, 50); 
    }
    FastLED.show(); // Show the updated LED
}
*/


void loop() {
    char* temp[5];
    temp[0] = "forward";
    temp[1] = "backward";
    temp[2] = "right";
    temp[3] = "left";
    temp[4] = "center";

    int i;
    char* curr;

    i = 0;

    while(1) {
      curr = temp[i % 5];
      lightHelper(curr);
      delay(1000);
      i++;
    }
    
}

