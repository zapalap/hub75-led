#include "WolframCaController.h"

const byte possibleNeighbors[8][3] = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}, {1, 0, 0}, {0, 1, 1}, {0, 1, 0}, {0, 0, 1}, {0, 0, 0}};
const byte possibleRules[18] = {30, 54, 60, 62, 90, 94, 102, 110, 122, 126, 150, 158, 182, 188, 190, 220, 222, 250};

WolframCaController::WolframCaController()
{
    rule = possibleRules[random(0, 18)];
    resetCurrentGen();
};

void WolframCaController::enter(const FrameContext &frame)
{
    rule = possibleRules[random(0, 18)];
    resetCurrentGen();
}

FrameContext WolframCaController::update(const FrameContext &frame)
{
    frameNumber++;

    if (rule > 254)
    {
        rule = 0;
    }

    handleJoy(frame.joyState);
    createNextGeneration();
    updateMatrix(frame.matrix);

    FrameContext updatedCtx(frame.matrix, frame.joyState, frame.selectButtonState);

    return updatedCtx;
};

void WolframCaController::createNextGeneration()
{
    for (int i = 1; i < MatrixBuffer::BOUND_X - 1; i++)
    {
        byte neighbors[3] = {0, 0, 0};
        neighbors[0] = currentGen[i - 1];
        neighbors[1] = currentGen[i];
        neighbors[2] = currentGen[i + 1];

        nextGen[i] = applyRule(neighbors);
    }
};

void WolframCaController::updateMatrix(ptrMatrixBuffer matrix)
{
    for (byte i = 0; i < MatrixBuffer::BOUND_X; i++)
    {
        matrix[0][i] = nextGen[i];
        currentGen[i] = nextGen[i];
    }

    for (int y = MatrixBuffer::BOUND_Y - 1; y - 1 >= 0; y--)
    {
        for (int i = 0; i < MatrixBuffer::BOUND_X; i++)
        {
            matrix[y][i] = matrix[y - 1][i];
        }
    }
};

void WolframCaController::handleJoy(JoyState joyState)
{
    if (joyState.x > 2200)
    {
        rule--;
    }

    if (joyState.x < 1500)
    {
        rule++;
    }

    if (joyState.y > 2200)
    {
        rule -= 10;
    }

    if (joyState.y < 1500)
    {
        rule += 10;
    }
}

byte WolframCaController::applyRule(byte neighbors[3])
{
    byte ruleArray[8];
    byte x = 7;

    for (int mask = 0x80; mask != 0; mask >>= 1)
    {
        (rule & mask) ? ruleArray[x] = 1 : ruleArray[x] = 0;
        x--;
    }

    for (byte i = 0; i < 8; i++)
    {
        if (possibleNeighbors[i][0] == neighbors[0] && possibleNeighbors[i][1] == neighbors[1] && possibleNeighbors[i][2] == neighbors[2])
        {
            return ruleArray[i];
        }
    }

    return 0;
};

void WolframCaController::resetCurrentGen()
{
    for (byte i = 0; i < MatrixBuffer::BOUND_X; i++)
    {
        currentGen[i] = 0;
    }
    currentGen[MatrixBuffer::BOUND_X / 2] = 1;
}