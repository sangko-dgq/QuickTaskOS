#include <Arduino.h>

#include "HAL/HAL.h"
#include "APP/APP.h"

void setup()
{
    Serial.begin(115200);

    HAL_Init();
    APP_Init();

}

void loop()
{
    APP_Update();

    //can't add any delay to match millis() here ( millisTaskManager.Running(millis()) ）
//    delay(800);
}