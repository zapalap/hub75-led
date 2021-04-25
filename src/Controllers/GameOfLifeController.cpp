#include "GameOfLifeController.h"
#include "../Common/ColorHelper.h"

#define BOUND_X 64
#define BOUND_Y 32

GameOfLifeController::GameOfLifeController(int B, int S)
{
    rule.B = B;
    rule.S = S;

    rules.push_back({3, 12345});
    rules.push_back({357, 1358});
    rules.push_back({345, 4567});
    rules.push_back({378, 235678});
    rules.push_back({3, 23});
    rules.push_back({3, 45678});
    rules.push_back({3678, 34678});
    rules.push_back({35678, 5678});
    rules.push_back({23, 36});
    rules.push_back({245, 368});
    rules.push_back({1357, 1357});

    generationNumber = 0;
    initialize();
}

void GameOfLifeController::enter(const FrameContext &frame)
{
    initializeFromMatrix(frame);
    randomSeed(ESP.getCycleCount());
    rule = rules[random(0, rules.size() - 1)];
}

FrameContext GameOfLifeController::update(const FrameContext &frame)
{
    handleJoy(frame.joyState);

    createNewGenerationAndUpdateMatrix(frame);
    generationNumber++;

    if (generationNumber > 9999)
    {
        generationNumber = 0;
    }

    FrameContext updatedContext(frame.matrix,
                                frame.joyState,
                                frame.selectButtonState);
    delay(20);
    return updatedContext;
}

void GameOfLifeController::createNewGenerationAndUpdateMatrix(const FrameContext &frame)
{
    byte nextGen[BOUND_Y][BOUND_X];
    for (int x = 0; x < BOUND_X; x++)
    {
        for (int y = 0; y < BOUND_Y; y++)
        {
            nextGen[y][x] = resolveRule(currentGen[y][x], countAliveNeighbors(x, y));
        }
    }

    for (int x = 0; x < BOUND_X; x++)
    {
        for (int y = 0; y < BOUND_Y; y++)
        {
            currentGen[y][x] = nextGen[y][x];
            frame.matrix[y][x] = nextGen[y][x];
        }
    }
}

void GameOfLifeController::initialize()
{
    randomSeed(ESP.getCycleCount());
    generationNumber = 0;
    for (byte x = 0; x < BOUND_X; x++)
    {
        for (byte y = 0; y < BOUND_Y; y++)
        {
            int val = random(0, 100);
            if (val > 50)
            {
                currentGen[y][x] = 1;
            }
            else
            {
                currentGen[y][x] = 0;
            }
        }
    }
}

void GameOfLifeController::initializeFromMatrix(const FrameContext &frame)
{
    generationNumber = 0;
    for (byte x = 0; x < BOUND_X; x++)
    {
        for (byte y = 0; y < BOUND_Y; y++)
        {
            currentGen[y][x] = frame.matrix[y][x];
        }
    }
}

byte GameOfLifeController::countAliveNeighbors(int x, int y)
{
    byte alive = 0;

    for (int nx = -1; nx <= 1; nx++)
    {
        for (int ny = -1; ny <= 1; ny++)
        {
            int dx = x + nx;
            int dy = y + ny;

            if (dx > BOUND_X - 1)
            {
                dx = 0;
            }

            if (dx < 0)
            {
                dx = BOUND_X - 1;
            }

            if (dy > BOUND_Y - 1)
            {
                dy = 0;
            }

            if (dy < 0)
            {
                dy = BOUND_Y - 1;
            }

            alive += currentGen[dy][dx];
        }
    }

    alive -= currentGen[y][x];

    return alive;
}

bool GameOfLifeController::ruleMet(int rule, byte aliveNieghbors)
{
    if (rule < 0)
    {
        return false;
    }

    while (rule != 0)
    {
        int digit = rule % 10;
        if (digit == aliveNieghbors)
        {
            return true;
        }

        rule /= 10;
    }

    return false;
}

byte GameOfLifeController::resolveRule(byte currentStatus, byte aliveNeighbors)
{
    // Birth (B)
    if (currentStatus == 0 && ruleMet(rule.B, aliveNeighbors))
    {
        return 1;
    }

    // Survive (S)
    if (currentStatus == 1 && ruleMet(rule.S, aliveNeighbors))
    {
        return 1;
    }

    return 0;
}

void GameOfLifeController::handleJoy(JoyState joyState)
{
    if (joyState.x > 2400 || joyState.x < 1300 || joyState.y > 2400 || joyState.y < 1300)
    {
        initialize();
    }
}
