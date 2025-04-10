#ifndef OBJECT_WORLD_H
#define OBJECT_WORLD_H

#include "object_screen.h"
#include "../affiliate/collider.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 position_ = glm::vec2(0, 0); // 世界位置
    Collider* collider_ = nullptr;

public:
    virtual void init() override {type_ = ObjectType::OBJECT_WORLD;}
    virtual void update(float dt) override;

    virtual ObjectWorld* clone() { return nullptr; }     // 需要用到clone的子类进行重写

    virtual void takeDamage(float) {}
    // getters and stters
    virtual glm::vec2 getPosition() const override { return position_; }
    void setPosition(const glm::vec2 &position);
    virtual void setRenderPosition(const glm::vec2 &render_position) override;
    virtual glm::vec2 getRenderPosition() override;
    Collider* getCollider() { return collider_; }
    void setCollider(Collider* collider) { collider_ = collider; }
    
};





#endif // OBJECT_WORLD_H