#include "hud_skill.h"
#include "../affiliate/sprite.h"

HUDSkill *HUDSkill::addHUDSkillChild(Object *parent, const std::string &file_path, glm::vec2 pos, float scale, Anchor anchor)
{
    auto hud_skill = new HUDSkill();
    hud_skill->init();
    hud_skill->icon_ = Sprite::addSpriteChild(hud_skill, file_path, scale, anchor);
    hud_skill->setRenderPosition(pos);
    if (parent) parent->addChild(hud_skill);
    return hud_skill;
}

void HUDSkill::render()
{
    // 先绘制浅色背景
    SDL_SetTextureColorModFloat(icon_->getTexture().texture, 0.3, 0.3, 0.3);
    auto pos = getRenderPosition() + icon_->getOffset();
    Game::getInstance().renderTexture(icon_->getTexture(), pos, icon_->getSize());
    SDL_SetTextureColorModFloat(icon_->getTexture().texture, 1.0, 1.0, 1.0);
    // 然后正常绘制
    ObjectScreen::render();
}

void HUDSkill::setPercentage(float percentage) 
{ 
    percentage = glm::clamp(percentage, 0.0f, 1.0f);
    percentage_ = percentage; 
    if (icon_){
        icon_->setPercentage(glm::vec2(1.0f, percentage));
    }   
}