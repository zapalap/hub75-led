#ifndef HUB75DMA_VIEW_H
#define HUB75DMA_VIEW_H

#include "View.h"
#include "..\Common\FrameContext.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class HUB75DMAView : public View
{
public:
    HUB75DMAView();
    void render(const FrameContext &frame);

private:
    MatrixPanel_I2S_DMA *display = nullptr;
    int rperiod;
    int gperiod;
    int bperiod;
};

#endif