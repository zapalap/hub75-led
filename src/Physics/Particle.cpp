#include "Particle.h"

Particle::Particle(double maxVelocity, double mass, double seekSpeed) : maxVelocity(maxVelocity), mass(mass), seekSpeed(seekSpeed)
{
}

void Particle::update(const FrameContext &frame)
{
    velocity.add(acceleration);
    location.add(velocity);
    velocity.limit(maxVelocity);
    acceleration.mult(0);

    if (location.x > 63)
    {
        location.x = 63;
    };

    if (location.x < 0)
    {
        location.x = 0;
    };

    if (location.y > 31)
    {
        location.y = 31;
    };

    if (location.y < 0)
    {
        location.y = 0;
    };
}

void Particle::draw(const FrameContext &frame)
{
    if ((location.x < 63 && location.x > 0) && (location.y < 31 && location.y > 0))
    {
        int ry = (int)location.y;
        int rx = (int)location.x;
        frame.matrix[ry][rx] = 1;
    }
}

void Particle::seek(const Vector &location)
{
    Vector direction = Vector::subtract(location, this->location);
    direction.normalize();
    direction.mult(seekSpeed);
    this->applyForce(direction);
}

void Particle::gravitateTo(Particle &particle)
{
    // Vector grav(0, 0);
    // double distance = this->distanceTo(particle.location);

    // grav.setMag(particle.mass / (distance * distance));
    // grav.setAngle(this->angleTo(particle));
    // this->applyForce(grav);
    Vector direction = Vector::subtract(particle.location, this->location);
    double dist = direction.mag();
    direction.normalize();
    direction.mult(particle.mass / (dist * dist));
    this->applyForce(direction);
}

void Particle::attract(Particle &particle)
{
    Vector direction = Vector::subtract(this->location, particle.location);
    double dist = direction.mag();
    direction.normalize();
    direction.mult(this->mass / (dist * dist));
    particle.applyForce(direction);
}

void Particle::applyForce(const Vector &force)
{
    acceleration.add(force);
}

double Particle::distanceTo(const Vector &target)
{
    Vector dist = Vector::subtract(this->location, target);
    return dist.mag();
}

double Particle::angleTo(Particle &particle)
{
    return atan2f(particle.location.y - this->location.y, particle.location.x - this->location.x);
}