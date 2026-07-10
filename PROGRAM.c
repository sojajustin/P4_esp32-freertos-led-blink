#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_RED   GPIO_NUM_5
#define LED_GREEN GPIO_NUM_2
#define LED_BLUE  GPIO_NUM_4

void led_task(void *pvParameter)
{
    gpio_num_t led_gpio = (gpio_num_t) pvParameter;
    uint8_t led_value = 0;
    TickType_t blink_time = 1000; // default

    // Decide blink time depending on GPIO
    if (led_gpio == LED_RED)   blink_time = 3000;
    if (led_gpio == LED_BLUE)  blink_time = 2000;
    if (led_gpio == LED_GREEN) blink_time = 1000;

    gpio_reset_pin(led_gpio);
    gpio_set_direction(led_gpio, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(led_gpio, led_value);
        led_value = !led_value;
        vTaskDelay(blink_time / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void app_main()
{
    xTaskCreate(
        &led_task,
        "red_led_task",
        2048,
        (void *)LED_RED,
        5,
        NULL
    );

    xTaskCreate(
        &led_task,
        "blue_led_task",
        2048,
        (void *)LED_BLUE,
        5,
        NULL
    );

    xTaskCreate(
        &led_task,
        "green_led_task",
        2048,
        (void *)LED_GREEN,
        5,
        NULL
    );
}
