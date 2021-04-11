#include "HUB75DMAView.h"

HUB75DMAView::HUB75DMAView()
{
    HUB75_I2S_CFG mxconfig;
    mxconfig.double_buff = true;

    display = new MatrixPanel_I2S_DMA(mxconfig);
    display->begin();
}

void HUB75DMAView::render(const FrameContext &frame)
{
    display->fillScreen(display->color444(0, 0, 0));

    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 32; y++)
        {
            if (frame.matrix[y][x] == 9)
            {
                continue;
            }

            if (frame.matrix[y][x] > 0)
            {
                display->drawPixel(x, y, display->color565(map(x, 0, 64, 0, 255), map(y, 0, 32, 0, 255), map(x, 0, 64, 255, 0)));
            }
        }
    }

    display->showDMABuffer();
    display->flipDMABuffer();

    delay(20);
}