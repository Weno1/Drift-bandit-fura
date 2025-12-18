#include "servo.hpp"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

Servo::Servo(uint8_t pin)
{
    gpio_set_function(pin, GPIO_FUNC_PWM);

    slice = pwm_gpio_to_slice_num(pin);
    channel = pwm_gpio_to_channel(pin);

    float div = (float)clock_get_hz(clk_sys) / 1'000'000.f;

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, div);

    pwm_config_set_wrap(&config, 20'000);

    pwm_init(slice, &config, false);
}

void Servo::enable()
{
    pwm_set_enabled(slice, true);
}

void Servo::disable()
{
    pwm_set_enabled(slice, false);
}

void Servo::write(uint8_t x)
{
    level = map((uint16_t)x, 0, 255, min, max);

    pwm_set_chan_level(slice, channel, level);
}

uint16_t Servo::read()
{
    return level;
}

uint16_t Servo::map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
