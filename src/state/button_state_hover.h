#ifndef BUTTON_STATE_HOVER_H
#define BUTTON_STATE_HOVER_H

#include "button_state.h"

class ButtonStateHover : public ButtonState {
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual bool handleEvents(SDL_Event& event) override;
};

#endif // BUTTON_STATE_HOVER_H
