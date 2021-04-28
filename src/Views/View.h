#ifndef VIEW_H
#define VIEW_H

#include "../Common/FrameContext.h"

class View
{
public:
    virtual void render(const FrameContext &frameContext);
};

#endif