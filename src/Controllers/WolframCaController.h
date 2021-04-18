#ifndef WOLFRAM_CA_CONTROLLER_H
#define WOLFRAM_CA_CONTROLLER_H

#include "Controller.h"

class WolframCaController : public Controller
{
public:
    WolframCaController();
    FrameContext update(const FrameContext &frame);
    void enter(const FrameContext &frame);

private:
    byte rule;
    int frameNumber;
    byte currentGen[64];
    byte nextGen[64];
    byte applyRule(byte neighbors[3]);
    void resetCurrentGen();
    void handleJoy(JoyState joyState);
    void createNextGeneration();
    void updateMatrix(ptrMatrixBuffer matrix);
};

#endif
