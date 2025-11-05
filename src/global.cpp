#include "global.h"
float glob_temperature = 0;
float glob_humidity = 0;

String WIFI_SSID = "TUAN KHAI";
String WIFI_PASS = "K41832837@";
String CORE_IOT_TOKEN;
String CORE_IOT_SERVER;
String CORE_IOT_PORT;

String ssid = "ESP32-YOUR NETWORK HERE!!!";
String password = "12345678";
String wifi_ssid = "KietNguyen";
String wifi_password = "88888888";
boolean isWifiConnected = false;
SemaphoreHandle_t xBinarySemaphoreInternet = xSemaphoreCreateBinary();