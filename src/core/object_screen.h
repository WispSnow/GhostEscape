#ifndef OBJECT_SCREEN_H
#define OBJECT_SCREEN_H

#include "object.h"

class ObjectScreen : public Object
{
protected:
    glm::vec2 render_position_ = glm::vec2(0, 0); // 渲染(屏幕)位置
    
public:
    virtual void init() override {type_ = ObjectType::OBJECT_SCREEN;}
    // getters and stters
    virtual glm::vec2 getRenderPosition() { return render_position_; }
    virtual void setRenderPosition(const glm::vec2 &render_position) { render_position_ = render_position; }
    virtual glm::vec2 getPosition() const { return glm::vec2(0); }
};





#endif // OBJECT_SCREEN_H