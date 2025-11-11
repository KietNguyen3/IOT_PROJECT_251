#include "printLCD.h"

void reportTempAndHumidity(LiquidCrystal_I2C &lcd){
    while(1){
        if(xSemaphoreTake(printOnLCDSemaphore, portMAX_DELAY)) 
            break;
    }
    
    TempHumid receiver;
    xQueuePeek(TempHumidQueue, &receiver, 100);

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

    xSemaphoreGive(printOnLCDSemaphore);
}
