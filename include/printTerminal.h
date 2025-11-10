#ifndef __PRINT_H__
#define __PRINT_H__

#include "global.h"
#include <cmath>

extern float glob_temperature;
extern float glob_humidity;
extern SemaphoreHandle_t printTempHumidSemaphore;

void printTH(void* pvParameters);
void printCondition(void* pvParameters);

#endif
