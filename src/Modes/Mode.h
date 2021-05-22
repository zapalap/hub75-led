#ifndef MODE_H
#define MODE_H

class Mode
{
public:
    virtual void init();
    virtual void update() = 0;
};

#endif