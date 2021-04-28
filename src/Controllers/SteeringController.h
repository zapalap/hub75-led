#ifndef __STEERINGCONTROLLER_H__
#define __STEERINGCONTROLLER_H__

#include "Controller.h"
#include "../Physics/Particle.h"

class SteeringController : public Controller
{
public:
    SteeringController();
    FrameContext update(const FrameContext &frame);
    void enter(const FrameContext &frame);

private:
    std::vector<Particle *> seekers;
    long frameNumber;
    Particle target;
    void renderTarget(const FrameContext &frame);
    void handleJoystick(JoyState joyState);
    void reset();
    void clearMatrix(const FrameContext &frame);
    double limit(double value, int min, int max);
};

#endif // __STEERINGCONTROLLER_H__