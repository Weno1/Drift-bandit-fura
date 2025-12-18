#ifndef SERVO_HPP
#define SERVO_HPP

#include <stdio.h>
#include "pico/stdlib.h"

class Servo
{
public:
    Servo(uint8_t pin);

    void enable();
    void disable();

    void write(uint8_t x);
    uint16_t read();

private:
    uint slice;
    uint channel;

    uint16_t level;

    uint16_t min = 800, max = 2200;

    uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);
};

#endif /*   SERVO_HPP   */