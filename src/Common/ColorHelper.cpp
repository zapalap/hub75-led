#include "ColorHelper.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

uint16_t ColorHelper::color565(uint8_t r, uint8_t g, uint8_t b)
{
    return MatrixPanel_I2S_DMA::color565(r, g, b);
}