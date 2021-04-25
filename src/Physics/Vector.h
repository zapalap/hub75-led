#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
    Vector();
    Vector(double x1, double y1);
    double x;
    double y;
    void add(const Vector &vector);
    static Vector subtract(Vector v1, Vector v2);
    void mult(double scalar);
    void div(double scalar);
    double mag();
    void setMag(double mag);
    void normalize();
    void limit(double max);
    void setAngle(double angle);
    double getAngle();
};

#endif