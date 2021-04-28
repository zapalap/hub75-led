
#ifndef __SEEKER_CONTROLLER_H__
#define __SEEKER_CONTROLLER_H__

#include "Controller.h"
#include "../Physics/Particle.h"
#include "../Physics/Vector.h"

struct SeekTarget
{
    int x;
    int y;
};

class SeekerController : public Controller
{
public:
    SeekerController();
    FrameContext update(const FrameContext &frame);
    void enter(const FrameContext &frame);

private:
    std::vector<Particle *> seekers;
    std::vector<SeekTarget> targets;
    long frameNumber;
    void clearMatrix(const FrameContext &frame);
    double limit(double value, int min, int max);

    static const int endState[32][64];
};

#endif // __STEERINGCONTROLLER_H__