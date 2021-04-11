#include "FrameContext.h"
#include "MatrixBuffer.h"

FrameContext::FrameContext(ptrMatrixBuffer matrixPtr, JoyState joy, byte selectButton)
{
    matrix = matrixPtr;
    joyState = joy;
    selectButtonState = selectButton;
};