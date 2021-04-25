#include "Vector.h"
#include <math.h>

Vector::Vector()
{
}

Vector::Vector(double x1, double y1)
{
    x = x1;
    y = y1;
}

void Vector::add(const Vector &vector)
{
    x += vector.x;
    y += vector.y;
}

Vector Vector::subtract(Vector v1, Vector v2)
{
    return Vector(v1.x - v2.x, v1.y - v2.y);
}

void Vector::mult(double scalar)
{
    x *= scalar;
    y *= scalar;
}

void Vector::div(double scalar)
{
    x /= scalar;
    y /= scalar;
}

double Vector::mag()
{
    double hypotenuse = sqrtf(((x * x) + (y * y)));
    return fabs(hypotenuse);
}

void Vector::setMag(double mag)
{
    this->normalize();
    this->mult(mag);
}

void Vector::normalize()
{
    double magnitude = mag();
    if (magnitude != 0)
    {
        div(magnitude);
    }
}

void Vector::limit(double max)
{
    double magnitude = mag();
    if (magnitude > max)
    {
        setMag(max);
    }
}

void Vector::setAngle(double angle)
{
    double mag = this->mag();
    this->x = cos(angle) * mag;
    this->y = sin(angle) * mag;
}

double Vector::getAngle()
{
    return atan2(this->y, this->x);
}