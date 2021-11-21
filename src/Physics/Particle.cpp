#include "Particle.h"

Particle::Particle(double maxVelocity, double mass, double seekSpeed) : maxVelocity(maxVelocity), mass(mass), seekSpeed(seekSpeed)
{
}

void Particle::update(const FrameContext &frame)
{
    velocity.add(acceleration);
    location.add(velocity);
    velocity.limit(maxVelocity);
    location.x = limit(location.x, -1, 75);
    location.y = limit(location.y, -1, 53);
    acceleration.mult(0);
}

void Particle::draw(const FrameContext &frame)
{
    if (!isWithinBounds(location.x, location.y))
        return;

    int ry = (int)location.y;
    int rx = (int)location.x;
    frame.matrix[ry][rx] = 1;
}

boolean Particle::isWithinBounds(double x, double y)
{
    return (y > 0 && y <= 31) && (x > 0 && x <= 63);
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

double Particle::limit(double value, int min, int max)
{
    if (value > max)
    {
        value = max;
        return value;
    }
    if (value < min)
    {
        value = min;
        return value;
    }
    return value;
}