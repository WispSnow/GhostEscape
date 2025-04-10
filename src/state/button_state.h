#ifndef BUTTON_STATE_H
#define BUTTON_STATE_H

#include "../core/object.h"
#include "../screen/hud_button.h"

class ButtonState : public Object {
protected:
    HUDButton* parent_ = nullptr;

public:
    virtual void onEnter() = 0;
    virtual void onExit() = 0;

    //getters and setters
    HUDButton* getParent() const { return parent_; }
    void setParent(HUDButton* parent) { parent_ = parent; }
};

#endif // BUTTON_STATE_H
