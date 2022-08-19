## HOW TO USE 

### 1 . (ENV. : Arduino)

#### HAL - Create Hardware Device

```c++
#include "HAL.h"

#ifdef ARDUINO
#define LED_ON     digitalWrite(PIN_LED, LOW)
#define LED_OFF    digitalWrite(PIN_LED,HIGH)
#define LED_INIT   pinMode(PIN_LED, OUTPUT)
#define LED_TOGGLE digitalWrite(PIN_LED, !digitalRead(PIN_LED))
#endif

static device_t d_led;
static void led_gpio_init()
{
    LED_INIT;
}
uint8_t s = HIGH;
static int led_control(device_t *dev, int cmd, void *args)
{
    if (TOGGLE == cmd) LED_TOGGLE;
    else if (ON == cmd) LED_ON;
    else if (OFF == cmd) LED_OFF;
    else return 0;
    return 1;
}
static device_ops_t dops_led = {.control = led_control};
static void led_register()
{
    d_led.dops = &dops_led;
    d_led.name = "Led";
    device_register(&d_led);
}

/* PUSH TO HAL INIT */
void led_init()
{
    led_gpio_init();
    led_register();
}
```

#### APP - Create APP Device

```c++
#include "MillisTaskManager.h"

static MillisTaskManager millisTaskManager;
static device_t* appd_led;
/* PUSH TO APP INIT */
static void led_task()
{
    device_control(appd_led, TOGGLE, nullptr);
}
void APP_Init()
{
    appd_led = device_find("Led"); 
    millisTaskManager.Register(led_task, 800);
}
void APP_Update()
{
    millisTaskManager.Running(millis());
}
```

#### Main - Init HAL & APP

```c++
#include "HAL/HAL.h"
#include "APP/APP.h"

void setup()
{
    HAL_Init();
    APP_Init();
}
void loop()
{
    APP_Update();
}
```

### 2. (ENV. : STC32G)

**TODO**

### 3. (ENV. : STM32Fxx)

**TODO**

