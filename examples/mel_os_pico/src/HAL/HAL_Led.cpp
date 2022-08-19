//
// Created by 22012 on 2022/8/19.
//

#include "HAL.h"

#ifdef ARDUINO
#define LED_ON     digitalWrite(PIN_LED, LOW)
#define LED_OFF    digitalWrite(PIN_LED,HIGH)
#define LED_INIT   pinMode(PIN_LED, OUTPUT)
#define LED_TOGGLE digitalWrite(PIN_LED, !digitalRead(PIN_LED))
#endif


/*创建一个LED设备*/
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

    /*向链表注册*/
    device_register(&d_led);
}


void led_init()
{
    led_gpio_init();
    led_register();
}








