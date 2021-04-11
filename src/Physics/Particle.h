#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector.h"
#include "..\Common\FrameContext.h"


class Particle
{
public:
    Particle(double maxVelocity, double seekSpeed);
    double maxVelocity;
    double seekSpeed;
    Vector location;
    Vector velocity;
    Vector acceleration;
    void update(const FrameContext &frame);
    void draw(const FrameContext &frameContext);
    void applyForce(const Vector &force);
    void seek(const Vector &location);
};

#endif