#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector.h"
#include "..\Common\FrameContext.h"

class Particle
{
public:
    Particle(double maxVelocity, double mass, double seekSpeed);
    double maxVelocity;
    double mass;
    double seekSpeed;
    Vector location;
    Vector velocity;
    Vector acceleration;
    void update(const FrameContext &frame);
    void draw(const FrameContext &frameContext);
    void applyForce(const Vector &force);
    void seek(const Vector &location);
    void gravitateTo(Particle &particle);
    void attract(Particle &particle);
    double distanceTo(const Vector &target);
    double angleTo(Particle &particle);
};

#endif