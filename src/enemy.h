#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "affiliate/sprite_anim.h"

class Enemy : public Actor
{
protected:
    enum class State{
        NORMAL,
        HURT,
        DIE
    };
    State current_state_ = State::NORMAL;
    
    Player* target_ = nullptr;
    SpriteAnim* anim_normal_ = nullptr;
    SpriteAnim* anim_hurt_ = nullptr;
    SpriteAnim* anim_die_ = nullptr;
    SpriteAnim* current_anim_ = nullptr;    // 这是个附加指针，不需要进行delete操作
    int score_ = 10;

public:
    static Enemy* addEnemyChild(Object* parent, glm::vec2 pos, Player* target);
    virtual void init() override;
    virtual void update(float dt) override;  // override the update function from Actor
    virtual void render() override;     // 如果超出屏幕区域就不要调用绘制函数
    // getters and setters
    Player* getTarget() { return target_; }
    void setTarget(Player* target) { target_ = target; }

private:
    void aim_target(Player* target);
    void checkState();
    void changeState(State new_state);
    void attack();
    void remove();
};








#endif // ENEMY_H