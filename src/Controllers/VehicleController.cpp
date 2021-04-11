#include "VehicleController.h"

const byte VehicleController::shipSprite[5][5] = {
    {1, 1, 0, 0, 0},
    {1, 1, 1, 0, 0},
    {0, 1, 1, 1, 0},
    {1, 1, 1, 0, 0},
    {1, 1, 0, 0, 0}};

const byte VehicleController::redSunSprite[5][5] = {
    {0, 1, 1, 0, 0},
    {1, 1, 1, 1, 0},
    {1, 1, 1, 1, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0}};

VehicleController::VehicleController() : dot(0.3, 0.02)
{
    dot.location.x = 15;
    dot.location.x = 6;

    x = 6;
    y = 12;
    blackSunx = 27;
    blackSuny = 13;
    redSunx = 58;
    redSuny = 8;
    frameNumber = 0;
    sunStep = 1;
}

void VehicleController::enter(const FrameContext &frame)
{
    clearMatrix(frame);
    for (int x = 0; x < 64; x++)
    {
        terrain[x] = 0;
    }
}

FrameContext VehicleController::update(const FrameContext &frame)
{
    frameNumber++;

    drawVehicle(frame);
    generateTerain(frame);
    handleJoy(frame.joyState);

    Vector shipLoc(x, y);
    dot.seek(shipLoc);
    dot.update(frame);
    dot.draw(frame);

    FrameContext updatedContext(frame.matrix, frame.joyState, frame.selectButtonState);
    return updatedContext;
}

void VehicleController::handleJoy(JoyState joyState)
{
    if (joyState.x > 2100)
    {
        x--;
        x = limit(x, 1, 58);
    }

    if (joyState.x < 1700)
    {
        x++;
        x = limit(x, 1, 58);
    }

    if (joyState.y > 2100)
    {
        y++;
        y = limit(y, 5, 28);
    }

    if (joyState.y < 1700)
    {
        y--;
        y = limit(y, 5, 28);
    }
}

void VehicleController::renderSprite(int sprx, int spry, const byte (*spritePtr)[5], const FrameContext &frame)
{
    for (int sx = 0; sx < 5; sx++)
    {
        for (int sy = 0; sy < 5; sy++)
        {
            frame.matrix[limit(spry - sy, 1, 31)][limit(sprx + sx, 0, 63)] = spritePtr[sy][sx];
        }
    }
}

void VehicleController::drawVehicle(const FrameContext &frame)
{
    clearMatrix(frame);
    renderSprite(x, y, shipSprite, frame);
}

byte VehicleController::getRandomHeight()
{

    int dieCast = random(0, 100);

    if (dieCast <= 1)
    {
        return random(4, 8);
    }

    if (dieCast <= 2)
    {
        return random(4, 10);
    }

    if (dieCast <= 65)
    {
        return random(2, 6);
    }

    if (dieCast <= 85)
    {
        return random(2, 4);
    }

    return random(1, 3);
}

void VehicleController::generateTerain(const FrameContext &frame)
{
    byte nextHeight = getRandomHeight();

    for (int x = 0; x < 63; x++)
    {
        terrain[x] = terrain[x + 1];
    }

    terrain[63] = nextHeight;

    for (int x = 0; x < 64; x++)
    {
        for (int y = 31; y >= 31 - terrain[x]; y--)
        {
            frame.matrix[y][x] = 2;
        }
    }

    renderSprite(redSunx, redSuny, redSunSprite, frame);
}

void VehicleController::clearMatrix(const FrameContext &frame)
{
    for (byte x = 0; x < 64; x++)
    {
        for (byte y = 0; y < 32; y++)
        {
            frame.matrix[y][x] = 0;
        }
    }
}

int VehicleController::limit(int value, int min, int max)
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