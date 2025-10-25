
#include <stdbool.h>
#include "app_bsp.h"
#include "led_strip.h"

static led_strip_handle_t led_strip;

void AppBSP_init()
{
    led_strip_config_t strip_config = {
        .strip_gpio_num = 8,
        .max_leds = 1,
        .led_model = LED_MODEL_WS2812,
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB};

    led_strip_rmt_config_t rmt_config = {};

    led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip);
}

void AppBSP_toggle_red()
{
    static bool is_on = false;
    is_on = !is_on;

    if (is_on)
    {
        led_strip_set_pixel(led_strip, 0, 255, 0, 0);
        led_strip_refresh(led_strip);
    }
    else
    {
        led_strip_clear(led_strip);
    }
}
