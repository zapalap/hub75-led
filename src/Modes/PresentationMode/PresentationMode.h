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

class PresentationMode : public Mode
{
public:
    PresentationMode();
    void init();
    void update();
    void nextController();
    bool ensureSelectPushed();

private:
    WiFiConnection wifiConnection;
    HUB75DMAView view;
    Ticker selectDebounceTicker;
    Ticker demoReelTicker;
    FrameContext *currentFrame;
    matrixBuffer buffer;
    ptrMatrixBuffer matrix = buffer;
    std::vector<Controller*> controllers;
    bool selectCheckPendning;
    bool selectPushPending;
    bool alreadyInitialized;
    int currentController = 0;
    long frameCounter = 0;
    void render(const FrameContext &frame);
    void handleSelectButton(const FrameContext &frame);
};

#endif