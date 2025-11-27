#include "neo_blinky.h"

// void neo_blinky(void *pvParameters) {
//     static Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
//     strip.begin();
//     strip.clear();
//     strip.show();

//     TempHumid receiver;

//     while (1) {
//         // Wait for queue data (non-blocking for too long)
//         if (xQueuePeek(TempHumidQueue, &receiver, 100)) {

//             strip.clear();

//             if (receiver.humidity > 90) {
//                 strip.setPixelColor(0, strip.Color(128, 0, 0));  // Dark Red
//                 Serial.println("TOO HUMID");
//             }
//             else if (receiver.humidity > 80) {
//                 strip.setPixelColor(0, strip.Color(220, 20, 60)); // Crimson
//             }
//             else if (receiver.humidity > 70) {
//                 strip.setPixelColor(0, strip.Color(255, 255, 0)); // Yellow
//             }
//             else if (receiver.humidity > 60) {
//                 strip.setPixelColor(0, strip.Color(0, 100, 0));   // Dark Green
//             }
//             else if (receiver.humidity > 50) {
//                 strip.setPixelColor(0, strip.Color(0, 255, 255)); // Cyan
//             }
//             else {
//                 strip.setPixelColor(0, strip.Color(0, 0, 255));   // Blue (default low humidity)
//             }

//             strip.show();
//         }

//         vTaskDelay(500);  // Update every 0.5 sec
//     }
// }

void neo_blinky(void *pvParameters) {
    static Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    strip.clear();
    strip.show();

    TempHumid receiver;
    
    // Base color (you can choose any color - this example uses cyan/blue)
    uint8_t baseR = 0;
    uint8_t baseG = 150;
    uint8_t baseB = 255;

    while (1) {
        // Wait for queue data (non-blocking for too long)
        if (xQueuePeek(TempHumidQueue, &receiver, 100)) {
            
            uint8_t brightness = 0;
            
            // Map humidity to brightness levels (0-255)
            if (receiver.humidity > 90) {
                brightness = 255;  // Maximum brightness - Critical humidity
                Serial.println("HUMIDITY: >90% - Maximum brightness");
            }
            else if (receiver.humidity > 80) {
                brightness = 200;  // Very high
                Serial.println("HUMIDITY: 80-90% - Very high brightness");
            }
            else if (receiver.humidity > 70) {
                brightness = 150;  // High
                Serial.println("HUMIDITY: 70-80% - High brightness");
            }
            else if (receiver.humidity > 60) {
                brightness = 100;  // Medium
                Serial.println("HUMIDITY: 60-70% - Medium brightness");
            }
            else if (receiver.humidity > 50) {
                brightness = 50;   // Low
                Serial.println("HUMIDITY: 50-60% - Low brightness");
            }
            else {
                brightness = 10;   // Very dim - Low humidity
                Serial.println("HUMIDITY: <50% - Very low brightness");
            }
            
            // Apply brightness to base color using PWM-like scaling
            uint8_t r = (baseR * brightness) / 255;
            uint8_t g = (baseG * brightness) / 255;
            uint8_t b = (baseB * brightness) / 255;
            
            strip.setPixelColor(0, strip.Color(r, g, b));
            strip.show();
        }

        vTaskDelay(500);  // Update every 0.5 sec
    }
}