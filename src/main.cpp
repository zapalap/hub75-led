#include "Arduino.h"
#include "Ticker.h"

#include "Common/MatrixBuffer.h"
#include "Common/FrameContext.h"

#include "Controllers/Controller.h"
#include "Controllers/GameOfLifeController.h"
#include "Controllers/WolframCaController.h"
#include "Controllers/SteeringController.h"
#include "Controllers/SeekerController.h"

#include "Views/View.h"
#include "Views/HUB75DMAView.h"

#define JOY_X 39
#define JOY_Y 36

#define SELECT_BUTTON 32

HUB75DMAView view;

WolframCaController caController;
SteeringController steeringController;
SeekerController seekerController;
GameOfLifeController golController(3, 12345);
Ticker selectDebounceTicker;
Ticker demoReelTicker;

FrameContext *currentFrame;

matrixBuffer buffer;
ptrMatrixBuffer matrix = buffer;

#define MAX_CONTROLLERS 4
Controller *controllers[MAX_CONTROLLERS] = {
    &caController,
    &seekerController,
    &golController,
    &steeringController};

bool selectCheckPendning;
bool selectPushPending;
int currentController = 0;
long frameCounter = 0;

void render(const FrameContext &frame);
void nextController();
void handleSelectButton(const FrameContext &frame);
bool ensureSelectPushed();

void setup()
{
    Serial.begin(115200);
    pinMode(JOY_X, INPUT);
    pinMode(JOY_Y, INPUT);
    pinMode(SELECT_BUTTON, INPUT_PULLUP);
    demoReelTicker.attach(
        5, +[]() { nextController(); });
}

void loop()
{
    frameCounter++;
    JoyState joyState;
    joyState.x = analogRead(JOY_X);
    joyState.y = analogRead(JOY_Y);

    FrameContext frame(matrix, joyState, HIGH);
    frame.numFrame = frameCounter;

    handleSelectButton(frame);

    FrameContext newFrame = controllers[currentController]->update(frame);
    newFrame.numFrame = frameCounter;
    currentFrame = &newFrame;
    render(newFrame);
}

void render(const FrameContext &frame)
{
    view.render(frame);
}

void nextController()
{
    long selected = 0;
    do
    {
        selected = random(100) % MAX_CONTROLLERS;
    } while (selected == currentController);

    currentController = selected;

    controllers[selected]->enter(*currentFrame);
}

void handleSelectButton(const FrameContext &frame)
{
    byte selectButtonState = digitalRead(SELECT_BUTTON);

    if (!selectCheckPendning && selectButtonState == LOW)
    {
        selectCheckPendning = true;

        selectDebounceTicker.once_ms(
            100, +[]() { ensureSelectPushed(); });
    }

    if (selectPushPending)
    {
        currentController++;

        if (currentController > MAX_CONTROLLERS - 1)
        {
            currentController = 0;
        }

        controllers[currentController]->enter(frame);
        selectPushPending = false;
    }
}

bool ensureSelectPushed()
{
    int switchState = digitalRead(SELECT_BUTTON);

    if (switchState == LOW)
    {
        selectPushPending = true;
    }

    selectCheckPendning = false;

    return true;
}
