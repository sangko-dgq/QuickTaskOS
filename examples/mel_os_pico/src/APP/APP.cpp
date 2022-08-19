//
// Created by 22012 on 2022/8/19.
//

#include "APP.h"
#include "../../lib/MillisTaskManager/MillisTaskManager.h"

static MillisTaskManager millisTaskManager;

static device_t* appd_led;
static void led_task()
{
    device_control(appd_led, TOGGLE, nullptr);
}

void APP_Init()
{
    appd_led = device_find("Led"); //检索到led实体
    millisTaskManager.Register(led_task, 100);
}

void APP_Update()
{
    millisTaskManager.Running(millis());
}

