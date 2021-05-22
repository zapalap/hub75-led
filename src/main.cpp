#include "Modes/Mode.h"
#include "Modes/PresentationMode/PresentationMode.h"

#define MAX_MODES 1

PresentationMode presentationMode;

Mode *modes[MAX_MODES] = {
    &presentationMode
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
