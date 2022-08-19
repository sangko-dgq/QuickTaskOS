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
    delay(800);
}