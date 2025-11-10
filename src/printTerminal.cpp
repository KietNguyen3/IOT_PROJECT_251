#include "printTerminal.h"

SemaphoreHandle_t printTempHumidSemaphore = xSemaphoreCreateBinary();

void printTH(void* pvParameters){
    while(1){    
        Serial.print("Temperature: ");
        Serial.print(glob_temperature);
        Serial.print("°C Humidity: ");
        Serial.print(glob_humidity);
        Serial.println("% ");

        xSemaphoreGive(printTempHumidSemaphore);
        vTaskDelay(5000);
    }
}

void printCondition(void* pvParameters){
    while(1){
        while(1){
            if(xSemaphoreTake(printTempHumidSemaphore, portMAX_DELAY))
                break;
        }
        if(glob_temperature == 0){
                Serial.println("Temperature initializing...");
        } 
        else if(glob_temperature > 25){
                Serial.println("Satisfactory Temperature");
        } 
        else if(glob_temperature > 20){
                Serial.println("Cool Temperature");
        } 
        else if(glob_temperature > 15){
                Serial.println("Freezing Temperature");
        }
    }
}