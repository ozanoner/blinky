
#include <stdbool.h>
#include "driver/gpio.h"
#include "app_bsp.h"

#define RED_LED_GPIO GPIO_NUM_18
#define BLUE_LED_GPIO GPIO_NUM_19

void AppBSP_init()
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << RED_LED_GPIO) | (1ULL << BLUE_LED_GPIO),
        .mode = GPIO_MODE_OUTPUT};

    gpio_config(&io_conf);

    gpio_set_level(BLUE_LED_GPIO, 1);
}

void AppBSP_toggle_red()
{
    static bool is_on = false;
    is_on = !is_on;
    gpio_set_level(RED_LED_GPIO, is_on ? 1 : 0);
}

void AppBSP_toggle_blue()
{
    static bool is_on = true;
    is_on = !is_on;
    gpio_set_level(BLUE_LED_GPIO, is_on ? 1 : 0);
}