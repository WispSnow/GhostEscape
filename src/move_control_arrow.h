#ifndef MOVE_CONTROL_ARROW_H
#define MOVE_CONTROL_ARROW_H

#include "raw/move_control.h"

class MoveControlArrow : public MoveControl
{
    void update(float dt) override;
};

#endif // MOVE_CONTROL_ARROW_H
