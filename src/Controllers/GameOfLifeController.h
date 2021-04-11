#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include "Controller.h"

struct Rule
{
    int B;
    int S;
};

class GameOfLifeController : public Controller
{
public:
    GameOfLifeController(int B, int S);
    FrameContext update(const FrameContext &frame);
    void enter(const FrameContext &frame);

private:
    Rule rule;
    std::vector<Rule> rules;
    int generationNumber;
    byte currentGen[32][64];
    void initialize();
    void initializeFromMatrix(const FrameContext &frame);
    byte countAliveNeighbors(int x, int y);
    byte resolveRule(byte currentStatus, byte aliveNeighbors);
    bool ruleMet(int rule, byte aliveNieghbors);
    void handleJoy(JoyState joyState);
    void createNewGenerationAndUpdateMatrix(const FrameContext &frame);
};

#endif