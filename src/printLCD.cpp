#include "printLCD.h"

bool button_flag = 0;
bool lastState = 0;
bool currentState;

void reportTempAndHumidity(LiquidCrystal_I2C &lcd){
    while(1){
        if(xSemaphoreTake(printOnLCDSemaphore, portMAX_DELAY)) 
            break;
    }

    TempHumid receiver;
    xQueuePeek(TempHumidQueue, &receiver, 100);

    currentState = digitalRead(SENSOR_PIN);
    if(currentState != lastState){
        button_flag = !button_flag;
        lastState = currentState;
        vTaskDelay(10);
    }

    if(button_flag){
        lcd.clear();
        lcd.home();
        lcd.print("Temp: ");
        lcd.print(receiver.temperature, 1);
        lcd.print(char(223));
        lcd.print("C");
        lcd.setCursor(0,1);
        lcd.print("Humidity: ");
        lcd.print(receiver.humidity, 1);
        lcd.print("%");
    }
    else{
        lcd.clear();
        lcd.home();
        if(receiver.temperature > 30){
            lcd.setCursor(0,0);
            lcd.print("Hot Temperature");
        }
        else if(receiver.temperature > 25){
            lcd.setCursor(0,0);
            lcd.print("Mid Temperature");
        }
        else if(receiver.temperature > 20){
            lcd.setCursor(0,0);
            lcd.print("Low Temperature");
        }
        if(receiver.humidity > 90){
            lcd.setCursor(0,1);
            lcd.print("                ");
            lcd.setCursor(0,1);
            lcd.print("High Humidity");
        }
        else if(receiver.humidity > 70){
            lcd.setCursor(0,1);
            lcd.print("               ");
            lcd.setCursor(0,1);
            lcd.print("Mid Humidity");
        }
        else if(receiver.humidity > 50){
            lcd.setCursor(0,1);
            lcd.print("               ");
            lcd.setCursor(0,1);
            lcd.print("Average Humidity");
        }
    }

    xSemaphoreGive(printOnLCDSemaphore);
}