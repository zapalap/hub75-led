#include "PresentationMode.h"

void nextCtrl(PresentationMode *mode);
void ensurePushed(PresentationMode *mode);

PresentationMode::PresentationMode()
{
}

void PresentationMode::init()
{
    if (alreadyInitialized)
    {
        return;
    }
    alreadyInitialized = true;
    controllers.push_back(new SeekerController());
    controllers.push_back(new SteeringController());
    controllers.push_back(new GameOfLifeController());
    pinMode(JOY_X, INPUT);
    pinMode(JOY_Y, INPUT);
    pinMode(SELECT_BUTTON, INPUT_PULLUP);
    demoReelTicker.attach(10, nextCtrl, this);
    JoyState joyState;
    joyState.x = analogRead(JOY_X);
    joyState.y = analogRead(JOY_Y);
    FrameContext frame(matrix, joyState, HIGH);
    currentFrame = &frame;
    controllers[currentController]->enter(*currentFrame);
}

void PresentationMode::update()
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

void PresentationMode::render(const FrameContext &frame)
{
    view.render(frame);
}

void PresentationMode::nextController()
{
    long selected = 0;
    do
    {
        selected = random(100) % controllers.size();
    } while (selected == currentController);

    currentController = selected;

    controllers[selected]->enter(*currentFrame);
}

void PresentationMode::handleSelectButton(const FrameContext &frame)
{
    byte selectButtonState = digitalRead(SELECT_BUTTON);

    if (!selectCheckPendning && selectButtonState == LOW)
    {
        selectCheckPendning = true;

        selectDebounceTicker.once_ms(
            100, ensurePushed, this);
    }

    if (selectPushPending)
    {
        currentController++;

        if (currentController > controllers.size())
        {
            currentController = 0;
        }

        controllers[currentController]->enter(frame);
        selectPushPending = false;
    }
}

bool PresentationMode::ensureSelectPushed()
{
    int switchState = digitalRead(SELECT_BUTTON);

    if (switchState == LOW)
    {
        selectPushPending = true;
    }

    selectCheckPendning = false;

    return true;
}

// The below functions are a workaround to allow Ticker methods to work with
// class methods. Ticker.h 'attach' and 'once' functions expect a callback_t which is an
// alias defined as typedef void (*callback_t)(void) (that is: a function pointer
// that takes void and returns void). This is not compatible with a function pointer
// to method signature. Using a lambda is also out of question as lambdas can decay
// to function pointers only if they do not capture any variables. In this case
// a lambda would have to capture 'this' pointer in order to invoke this->nextController()
// or this->ensureSelectPushed(). Which would immediately make it incomaptible with
// callback_t as it's currently defined. The only solution is to create a free function
// that takes the mode instace and invokes the required public function. As this can
// be passed as a function pointer.
void nextCtrl(PresentationMode *mode)
{
    mode->nextController();
}

void ensurePushed(PresentationMode *mode)
{
    mode->ensureSelectPushed();
}
