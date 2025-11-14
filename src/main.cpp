#include "global.h"

#include "led_blinky.h"
#include "neo_blinky.h"
#include "temp_humi_monitor.h"
#include "mainserver.h"
// #include "tinyml.h"
#include "coreiot.h"
#include "printTerminal.h"

// include task
#include "task_check_info.h"
#include "task_toogle_boot.h"
#include "task_webserver.h"
#include "task_core_iot.h"

#define LED_PIN 48
#define SENSOR_PIN 4

void setup()
{
  delay(3000);
  Serial.begin(115200);
  Serial.println("Booted successfully");
  //startSTA();
  // pinMode(LED_GPIO, OUTPUT);
  //check_info_File(0);

  //--IOAS Sensor--//
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);



  xTaskCreate(led_blinky, "Task LED Blink", 2048, NULL, 1, NULL);
  // xTaskCreate(printCondition, "Print Condition", 2048, NULL, 1, NULL);
  xTaskCreatePinnedToCore(neo_blinky, "Task NEO Blink", 2048, NULL, 1, NULL, 1);
  xTaskCreate(temp_humi_monitor, "Task TEMP HUMI Monitor", 8192, NULL, 2, NULL);
  // xTaskCreate(printTH, "Print Temp and Humidity", 2048, NULL, 1, NULL);

  xTaskCreate(main_server_task, "Task Main Server" ,8192  ,NULL  ,2 , NULL);
  // xTaskCreate( tiny_ml_task, "Tiny ML Task" ,2048  ,NULL  ,2 , NULL);
  // xTaskCreate(coreiot_task, "CoreIOT Task" ,8192  ,NULL  ,2 , NULL);
  // xTaskCreate(Task_Toogle_BOOT, "Task_Toogle_BOOT", 4096, NULL, 2, NULL);
}


void loop()
{
  // if (check_info_File(1))
  // {
  //   if (!Wifi_reconnect())
  //   {
  //     Webserver_stop();
  //   }
  //   else
  //   {
  //     CORE_IOT_reconnect();
  //   }
  // }
  // Webserver_reconnect();
  
}