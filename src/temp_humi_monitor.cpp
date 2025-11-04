#include "temp_humi_monitor.h"
#define DHTPIN 2
#define DHTTYPE DHT11

//DHT20 dht20;
DHT dht(DHTPIN, DHTTYPE);
//LiquidCrystal_I2C lcd(33,16,2);

// NOTE: CODE WHEN USING DHT20 LIBRARIES AND RELATING PERIPHERALS
// void temp_humi_monitor(void *pvParameters){

//     Wire.begin(11, 12);
//     Serial.begin(115200);
//     dht20.begin();

//     while (1){
//         /* code */
        
//         dht20.read();
//         // Reading temperature in Celsius
//         float temperature = dht20.getTemperature();
//         // Reading humidity
//         float humidity = dht20.getHumidity();

        

//         // Check if any reads failed and exit early
//         if (isnan(temperature) || isnan(humidity)) {
//             Serial.println("Failed to read from DHT sensor!");
//             temperature = humidity =  -1;
//             //return;
//         }

//         //Update global variables for temperature and humidity
//         glob_temperature = temperature;
//         glob_humidity = humidity;

//         // Print the results
        
//         Serial.print("Humidity: ");
//         Serial.print(humidity);
//         Serial.print("%  Temperature: ");
//         Serial.print(temperature);
//         Serial.println("°C");
        
//         vTaskDelay(5000);
//     }
    
// }

void temp_humi_monitor(void *pvParameters) {
    dht.begin();

    while (1) {
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();

        if (isnan(temperature) || isnan(humidity)) {
            Serial.println("Failed to read from DHT11 sensor!");
        } else {
            Serial.print("Humidity: ");
            Serial.print(humidity);
            Serial.print("%  Temperature: ");
            Serial.print(temperature);
            Serial.println("°C");
        }

        vTaskDelay(3000); // delay 5 seconds
    }
}
