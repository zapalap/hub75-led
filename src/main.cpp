#include "Arduino.h"
#include "Ticker.h"

#include "Common\MatrixBuffer.h"
#include "Common\FrameContext.h"

#include "Controllers\Controller.h"
#include "Controllers\GameOfLifeController.h"
#include "Controllers\CellularAutomataController.h"
#include "Controllers\VehicleController.h"
#include "Controllers\SteeringController.h"

#include "Views\View.h"
#include "Views\HUB75DMAView.h"

#define JOY_X 39
#define JOY_Y 36

#define SELECT_BUTTON 32

HUB75DMAView view;

CellularAutomataController caController;
VehicleController vehicleController;
SteeringController steeringController;
GameOfLifeController golController(3, 12345);
Ticker selectDebounceTicker;
Ticker demoReelTicker;

FrameContext *currentFrameContext;

matrixBuffer buffer;
ptrMatrixBuffer matrix = buffer;

#define MAX_CONTROLLERS 3
Controller *controllers[MAX_CONTROLLERS] = {
    &caController,
    // &vehicleController,
    &golController,
    &steeringController};

bool selectCheckPendning;
bool selectPushPending;
int currentController = 0;

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
        3, +[]() { nextController(); });
}

void loop()
{
    JoyState joyState;
    joyState.x = analogRead(JOY_X);
    joyState.y = analogRead(JOY_Y);

    FrameContext frame(matrix, joyState, HIGH);

    handleSelectButton(frame);

    FrameContext newFrame = controllers[currentController]->update(frame);
    currentFrameContext = &newFrame;
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

    controllers[selected]->enter(*currentFrameContext);
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
