#ifndef MOVE_CONTROL_H
#define MOVE_CONTROL_H

#include "../core/object.h"
class Actor;
class MoveControl : public Object
{
protected:
    bool is_up_ = false;
    bool is_down_ = false;
    bool is_left_ = false;
    bool is_right_ = false;
    Actor* parent_ = nullptr;
    float max_speed_ = 500.0f;

public:
    void update(float dt) override;
    // void checkInput();
    virtual bool handleEvents(SDL_Event& event) override;
    
    // getters
    bool isUp() const { return is_up_; }
    bool isDown() const { return is_down_; }
    bool isLeft() const { return is_left_; }
    bool isRight() const { return is_right_; }
    Actor* getParent() const { return parent_; }
    float getMaxSpeed() const { return max_speed_; }

    // setters
    void setParent(Actor* actor) { parent_ = actor; }
    void setMaxSpeed(float speed) { max_speed_ = speed; }

};

#endif // MOVE_CONTROL_H
