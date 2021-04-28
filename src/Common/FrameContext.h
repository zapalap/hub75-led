#ifndef FRAME_CONTEXT_H
#define FRAME_CONTEXT_H

#include "../Common/MatrixBuffer.h"

struct JoyState
{
    int x;
    int y;
};

class FrameContext
{
public:
    FrameContext(ptrMatrixBuffer matrixPtr, JoyState joy, byte selectButton);
    long numFrame;
    ptrMatrixBuffer matrix;
    JoyState joyState;
    byte selectButtonState;
};

#endif
