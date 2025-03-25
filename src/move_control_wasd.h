#ifndef MOVE_CONTROL_WASD_H
#define MOVE_CONTROL_WASD_H

#include "raw/move_control.h"

class MoveControlWASD : public MoveControl
{
    void update(float dt) override;
};
#endif // MOVE_CONTROL_WASD_H
