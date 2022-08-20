//
// Created by 22012 on 2022/8/20.
//

#ifndef PICO_TEST_HAL_H
#define PICO_TEST_HAL_H

#include "Arduino.h"
#include "../lib/QuickTaskOS/src/os_device.h"
#include "../lib/QuickTaskOS/src/os_task.h"

void HAL_Init();
void HAL_Update();
extern OSTask osTask;

void led_device_init();
#define PIN_LED 21
enum LED_CMD{ TOGGLE, ON, OFF };


#endif //PICO_TEST_HAL_H
