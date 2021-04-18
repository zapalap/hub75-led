#include "HUB75DMAView.h"

HUB75DMAView::HUB75DMAView()
{
    HUB75_I2S_CFG mxconfig;
    mxconfig.double_buff = true;

    display = new MatrixPanel_I2S_DMA(mxconfig);
    display->begin();

    rperiod = 1;
    gperiod = 1;
    bperiod = 1;
}

void HUB75DMAView::render(const FrameContext &frame)
{
    display->fillScreen(display->color444(0, 0, 0));

    int rstep = 64;
    int gstep = 32;
    int bstep = 64;

    if (frame.numFrame % 16 == 0)
    {
        rperiod = (frame.numFrame % rstep) + 1;
        gperiod = (frame.numFrame % gstep) + 1;
        bperiod = (frame.numFrame % bstep) + 1;
    }

    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 32; y++)
        {
            if (frame.matrix[y][x] == 1)
            {
                long r = map(x, 0, 64, 0, 255);
                long g = map(y, 0, 32, 255, 0);
                long b = map(x, 0, 64, 255, 0);

                display->drawPixel(x, y, display->color565(r, g, b));
                continue;
            }

            if (frame.matrix[y][x] > 0)
            {
                display->drawPixel(x, y, frame.matrix[y][x]);
            }
        }
    }

    display->showDMABuffer();
    display->flipDMABuffer();

    delay(20);
}