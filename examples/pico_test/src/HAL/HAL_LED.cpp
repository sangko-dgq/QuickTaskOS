//
// Created by 22012 on 2022/8/20.
//
#include "HAL.h"

#ifdef ARDUINO
#define LED_ON digitalWrite(PIN_LED, LOW)
#define LED_OFF digitalWrite(PIN_LED, HIGH)
#define LED_INIT pinMode(PIN_LED, OUTPUT)
#define LED_TOGGLE digitalWrite(PIN_LED, !digitalRead(PIN_LED))
#endif

/* Abstract a hardware device */
static device_t hd_led;


/* Custom a device-control-static-functions */
static int led_control(device_t *dev, int cmd, void *args)
{
    if (TOGGLE == cmd)
        LED_TOGGLE;
    else if (ON == cmd)
        LED_ON;
    else if (OFF == cmd)
        LED_OFF;
    else
        return 0;
    return 1;
}

/* Put the custom control function to the OS-control-fnpointer */
static device_ops_t dops_led = {.control = led_control};

/* Register to OS*/
static void led_register()
{
    hd_led.dops = &dops_led;
    hd_led.name = "Led";

    device_register(&hd_led);
    osTask.Register(reinterpret_cast<void (*)()>(led_control), 800);

}

/* Custom a gpio-init-funtion*/
static void led_gpio_init()
{ LED_INIT; }
/* Main : Functions for main thread calls*/
void led_device_init()
{
    led_gpio_init();
    led_register();

}