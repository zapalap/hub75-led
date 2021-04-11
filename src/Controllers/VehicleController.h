#ifndef VEHICLE_H
#define VEHICLE_H

#include "Controller.h"
#include "../Physics/Particle.h"

class VehicleController : public Controller
{
public:
    VehicleController();
    FrameContext update(const FrameContext &frame);
    void enter(const FrameContext &frame);

private:
    char x;
    char y;
    char blackSunx;
    char blackSuny;
    char redSunx;
    char redSuny;
    char sunStep;
    long frameNumber;
    Particle dot;
    byte terrain[64];
    void handleJoy(JoyState joyState);
    void drawVehicle(const FrameContext &frame);
    int limit(int value, int min, int max);
    void clearMatrix(const FrameContext &frame);
    void generateTerain(const FrameContext &frameContext);
    byte getRandomHeight();
    void renderSprite(int x, int y, const byte (*spritePtr)[5], const FrameContext &frameContext);

    static const byte shipSprite[5][5];
    static const byte redSunSprite[5][5];
};

#endif