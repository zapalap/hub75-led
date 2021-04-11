#ifndef CELLULAR_CA_CONTROLLER_H
#define CELLULAR_CA_CONTROLLER_H

#include "Controller.h"

class CellularAutomataController : public Controller
{
public:
    CellularAutomataController();
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
