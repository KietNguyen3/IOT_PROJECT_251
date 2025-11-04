#include "neo_blinky.h"

static uint8_t count = 0;

void neo_blinky(void *pvParameters){

    static Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    static bool initialized = false;
    
    if(!initialized) {
        vTaskDelay(100);
        strip.begin();
        strip.clear();
        strip.show();
        vTaskDelay(100);
        strip.clear();
        strip.show();
        initialized = true;
    }

    while(1) {
        if(++count > 2) count = 0;
        switch(count){
            case 0:
                strip.setPixelColor(0, strip.Color(255, 165, 0)); // Set pixel 0 to red
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
        // Wait for 500 milliseconds
        vTaskDelay(500);

        // // Set the pixel to off
        // strip.setPixelColor(0, strip.Color(0, 0, 0)); // Turn pixel 0 off
        // strip.show(); // Update the strip

        // // Wait for another 500 milliseconds
        // vTaskDelay(500);
    }
}