#include "Modes/Mode.h"
#include "Modes/WeatherStationMode/WeatherStationMode.h"
#include "Modes/PresentationMode/PresentationMode.h"
#include <Ticker.h>

#define MAX_MODES 1
#define MODE_SWITCH_INTERVAL_SEC 30

// WeatherStationMode weatherStationMode;
PresentationMode presentationMode;

Ticker modeSwitchTicker;

Mode *modes[MAX_MODES] = {
    &presentationMode,
};

volatile int currentMode = 0;

void switchMode();

void setup()
{
    Serial.begin(115200);
    // modeSwitchTicker.attach(MODE_SWITCH_INTERVAL_SEC, switchMode);

    modes[currentMode]->init();
}

void loop()
{
    modes[currentMode]->update();
}

void switchMode() {
    currentMode++;
    if(currentMode >= MAX_MODES) {
        currentMode = 0;
    }
    
    Serial.println("Switching modes (" + String(currentMode) + ")");
}
