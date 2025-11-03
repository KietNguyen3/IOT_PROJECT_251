#include "neo_blinky.h"



void neo_blinky(void *pvParameters){

    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    // Set all pixels to off to start
    strip.clear();
    strip.show(); 

    static uint8_t count = 0;

    while(1) {
        switch(count){
            case 0:
                strip.setPixelColor(0, strip.Color(255, 0, 0)); // Set pixel 0 to red
                strip.show(); // Update the strip
                break;
            case 1:
                strip.setPixelColor(0, strip.Color(0, 255, 0)); // Set pixel 0 to red
                strip.show(); // Update the strip
                break;
            case 2:
                strip.setPixelColor(0, strip.Color(0, 0, 255)); // Set pixel 0 to red
                strip.show(); // Update the strip
                break;
        }
        if(++count > 2) count = 0;
        // Wait for 500 milliseconds
        vTaskDelay(500);

        // // Set the pixel to off
        // strip.setPixelColor(0, strip.Color(0, 0, 0)); // Turn pixel 0 off
        // strip.show(); // Update the strip

        // // Wait for another 500 milliseconds
        // vTaskDelay(500);
    }
}