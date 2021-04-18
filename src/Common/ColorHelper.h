#ifndef COLOR_HELPER_H
#define COLOR_HELPER_H
#include <Arduino.h>

class ColorHelper
{
public:
    static uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
};

#endif