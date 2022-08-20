#include <Arduino.h>
#include "HAL/HAL.h"

void setup()
{
    HAL_Init();
}

void loop()
{
   HAL_Update();
}