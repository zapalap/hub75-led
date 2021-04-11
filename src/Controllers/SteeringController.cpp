#include "SteeringController.h"

SteeringController::SteeringController()
{
    reset();
}

void SteeringController::enter(const FrameContext &frame)
{
    seekers.clear();
    randomSeed(ESP.getCycleCount());

    for (byte x = 0; x < 64; x++)
    {
        for (byte y = 0; y < 32; y++)
        {
            if (x % 2 == 0 && y % 2 == 0 && frame.matrix[y][x] > 0)
            {
                Particle seeker(0.5, 0.02);
                seeker.location.x = x;
                seeker.location.y = y;
                seekers.push_back(seeker);
            }
        }
    }
}

FrameContext SteeringController::update(const FrameContext &frame)
{
    frameNumber++;

    if (frameNumber % 200 == 0)
    {
        target.x = random(10, 50);
        target.y = random(5, 25);
    }

    clearMatrix(frame);

    for (auto &&seeker : seekers)
    {
        seeker.seek(target);
        seeker.update(frame);
        seeker.draw(frame);
    }

    handleJoystick(frame.joyState);
    renderTarget(frame);

    FrameContext updatedContext(frame.matrix, frame.joyState, frame.selectButtonState);
    return updatedContext;
}

void SteeringController::renderTarget(const FrameContext &frame)
{
    // int tx = roundFixed(target.x).getInteger();
    // int ty = roundFixed(target.y).getInteger();
    // frame.matrix[ty][tx] = 1;
}

void SteeringController::clearMatrix(const FrameContext &frame)
{
    for (byte x = 0; x < 64; x++)
    {
        for (byte y = 0; y < 32; y++)
        {
            frame.matrix[y][x] = 0;
        }
    }
}

void SteeringController::handleJoystick(JoyState joyState)
{
    if (joyState.x > 2100)
    {
        target.x -= 1;
        target.x = limit(target.x, 0, 64);
    }

    if (joyState.x < 1600)
    {
        target.x += 1;
        target.x = limit(target.x, 0, 64);
    }

    if (joyState.y > 2100)
    {
        target.y += 1;
        target.y = limit(target.y, 0, 32);
    }

    if (joyState.y < 1600)
    {
        target.y -= 1;
        target.y = limit(target.y, 0, 32);
    }
}

void SteeringController::reset()
{
    target.x = 32;
    target.y = 16;
    seekers.clear();

    for (int i = 0; i < 10; i++)
    {
        Particle seeker(0.5, 0.02);
        seeker.location.x = random(1, 63);
        seeker.location.y = random(1, 31);
        seekers.push_back(seeker);
    }
}

double SteeringController::limit(double value, int min, int max)
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