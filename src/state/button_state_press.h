#ifndef BUTTON_STATE_PRESS_H
#define BUTTON_STATE_PRESS_H

#include "button_state.h"

class ButtonStatePress : public ButtonState {
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual bool handleEvents(SDL_Event& event) override;
};

#endif // BUTTON_STATE_PRESS_H
