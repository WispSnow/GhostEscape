#ifndef SPELL_H
#define SPELL_H

#include "../core/object_world.h"
#include "../affiliate/sprite_anim.h"

class Spell : public ObjectWorld
{
protected:
    std::string file_path_;     // 这两个变量是为了克隆时复制
    float scale_ = 1.0f;
    SpriteAnim* sprite_ = nullptr;
    float damage_ = 60.0f;
public:
    static Spell* addSpellChild(Object* parent, const std::string& file_path, glm::vec2 pos, float damage, float scale = 1.0f, Anchor anchor = Anchor::CENTER);
    void update(float dt) override;

    Spell* clone();

    // getters and setters
    float getDamage() const { return damage_; }
    void setDamage(float damage) { damage_ = damage; }
    SpriteAnim* getSpriteAnim() const { return sprite_; }
    void setSpriteAnim(SpriteAnim* sprite) { sprite_ = sprite; }

private:
    void attack();
};



#endif  // SPELL_H