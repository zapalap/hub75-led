#ifndef PRESENTATION_MODE_H
#define PRESENTATION_MODE_H

#include "../Mode.h"

#include "Arduino.h"
#include "Ticker.h"

#include "Common/MatrixBuffer.h"
#include "Common/FrameContext.h"
#include "Common/WiFiConnection.h"
#include <HTTPClient.h>

#include "Controllers/Controller.h"
#include "Controllers/GameOfLifeController.h"
#include "Controllers/WolframCaController.h"
#include "Controllers/SteeringController.h"
#include "Controllers/SeekerController.h"

#include "Views/View.h"
#include "Views/HUB75DMAView.h"

#include <ArduinoJson.h>

#define JOY_X 39
#define JOY_Y 36

#define SELECT_BUTTON 32

#define MAX_CONTROLLERS 4

class PresentationMode : public Mode
{
public:
    PresentationMode() : golController(3, 12345),
                         controllers{
                             &caController,
                             &seekerController,
                             &golController,
                             &steeringController} {};
    void init();
    void update();
    void nextController();
    bool ensureSelectPushed();

private:
    WiFiConnection wifiConnection;
    HUB75DMAView view;
    WolframCaController caController;
    SteeringController steeringController;
    SeekerController seekerController;
    GameOfLifeController golController;
    Ticker selectDebounceTicker;
    Ticker demoReelTicker;
    FrameContext *currentFrame;
    matrixBuffer buffer;
    ptrMatrixBuffer matrix = buffer;
    Controller *controllers[MAX_CONTROLLERS];
    bool selectCheckPendning;
    bool selectPushPending;
    int currentController = 0;
    long frameCounter = 0;
    void render(const FrameContext &frame);
    void handleSelectButton(const FrameContext &frame);
};

#endif