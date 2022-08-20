//
// Created by 22012 on 2022/8/20.
//

#include "HAL.h"
OSTask osTask;

void HAL_Init()
{
    led_device_init();

}

void HAL_Update()
{
    osTask.Running(millis());
}