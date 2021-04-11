#include "Particle.h"

Particle::Particle(double maxVelocity, double seekSpeed)
{
    this->maxVelocity = maxVelocity;
    this->seekSpeed = seekSpeed;
}

void Particle::update(const FrameContext &frame)
{
    velocity.add(acceleration);
    location.add(velocity);
    velocity.limit(maxVelocity);
    acceleration.mult(0);

    if (location.x > 63)
    {
        location.x = 0;
    };

    if (location.x < 0)
    {
        location.x = 63;
    };

    if (location.y > 31)
    {
        location.y = 0;
    };

    if (location.y < 0)
    {
        location.y = 31;
    };
}

void Particle::draw(const FrameContext &frame)
{
    if ((location.x < 63 && location.x > 1) && (location.y < 31 && location.y > 1))
    {
        int ry = round(location.y);
        int rx = round(location.x);
        frame.matrix[ry][rx] = 1;
    }
}

void Particle::seek(const Vector &location)
{
    Vector direction = Vector::subtract(location, this->location);
    direction.normalize();
    direction.mult(seekSpeed);
    direction.mult(-1);
    this->applyForce(direction);
}

void Particle::applyForce(const Vector &force)
{
    acceleration.add(force);
}