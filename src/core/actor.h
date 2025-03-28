#ifndef ACTOR_H
#define ACTOR_H

#include "object_world.h"
#include "../raw/move_control.h"

class Stats;
class AffiliateBar;
class Actor : public ObjectWorld
{
protected:
    MoveControl* move_control_ = nullptr; // 移动控制
    Stats *stats_ = nullptr; // 角色属性
    AffiliateBar* health_bar_ = nullptr;  // 生命条
    glm::vec2 velocity_ = glm::vec2(0, 0); // 速度
    float max_speed_ = 100.0f; // 最大速度大小

public:
    virtual void update(float dt) override;
    
    virtual void takeDamage(float damage) override;
    void move(float dt);    // 移动

    void removeMoveControl();
    
    // getters and setters
    MoveControl* getMoveControl() const { return move_control_; }
    void setMoveControl(MoveControl *move_control);
    glm::vec2 getVelocity() const { return velocity_; }
    void setVelocity(const glm::vec2 &velocity) { velocity_ = velocity; }
    float getMaxSpeed() const { return max_speed_; }
    void setMaxSpeed(float max_speed) { max_speed_ = max_speed; }
    Stats *getStats() const { return stats_; }
    void setHealthBar(AffiliateBar* health_bar) { health_bar_ = health_bar; }
    AffiliateBar* getHealthBar() const { return health_bar_; }
    void setStats(Stats *stats) { stats_ = stats; }
    bool getIsAlive() const;

private:
    void updateHealthBar();
};

#endif // ACTOR_H