#ifndef __PRINT_LCD_H__
#define __PRINT_LCD_H__

#include "global.h"
#include "LiquidCrystal_I2C.h"

extern SemaphoreHandle_t printOnLCDSemaphore;
void reportTempAndHumidity(LiquidCrystal_I2C &lcd);

extern bool button_flag;
extern bool lastState;
extern bool currentState;
extern LiquidCrystal_I2C lcd;

#endif