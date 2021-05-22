#include "Modes/Mode.h"
#include "Modes/WeatherStationMode/WeatherStationMode.h"

#define MAX_MODES 1

WeatherStationMode weatherStationMode;

Mode *modes[MAX_MODES] = {
    &weatherStationMode
};

int currentMode = 0;

void setup()
{
    modes[currentMode]->init();
}

void loop()
{
    modes[currentMode]->update();
}
