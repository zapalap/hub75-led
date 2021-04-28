#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Common/FrameContext.h"
#include "../Common/MatrixBuffer.h"

class Controller
{
public:
    virtual FrameContext update(const FrameContext &frame) = 0;
    virtual void enter(const FrameContext &frame){};
};

#endif