#include "SteeringController.h"

SteeringController::SteeringController() : target(0.5, 10, 0.5)
{
    target.location.x = 32;
    target.location.y = 16;
    // reset();
}

void SteeringController::enter(const FrameContext &frame)
{
    randomSeed(ESP.getCycleCount());

    for (Particle *seeker : seekers)
    {
        delete (seeker);
    }

    seekers.clear();

    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 32; y++)
        {
            bool shouldBeSeeker = frame.matrix[y][x] > 0;
            if (shouldBeSeeker)
            {
                Particle *seeker = new Particle(0.5, 0.5, 0.02);
                seeker->location.x = (double)x;
                seeker->location.y = (double)y;
                seekers.push_back(seeker);
            }
        }
    }
}

FrameContext SteeringController::update(const FrameContext &frame)
{
    frameNumber++;

    // if (frameNumber % 20 == 0)
    // {
    //     target.location.x = random(0, 63);
    //     target.location.y = random(0, 31);
    // }

    clearMatrix(frame);

    for (Particle *seeker : seekers)
    {
        seeker->gravitateTo(target);
        seeker->update(frame);
        seeker->draw(frame);
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
        target.location.x -= 1;
        target.location.x = limit(target.location.x, 0, 64);
    }

    if (joyState.x < 1600)
    {
        target.location.x += 1;
        target.location.x = limit(target.location.x, 0, 64);
    }

    if (joyState.y > 2100)
    {
        target.location.y += 1;
        target.location.y = limit(target.location.y, 0, 32);
    }

    if (joyState.y < 1600)
    {
        target.location.y -= 1;
        target.location.y = limit(target.location.y, 0, 32);
    }
}

void SteeringController::reset()
{
    target.location.x = 32;
    target.location.y = 16;

    for (auto seeker : seekers)
    {
        delete (seeker);
    }

    seekers.clear();

    for (int i = 0; i < 10; i++)
    {
        Particle *seeker = new Particle(0.5, 0.5, 0.02);
        seeker->location.x = random(1, 63);
        seeker->location.y = random(1, 31);
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