#include "object_world.h"
#include "scene.h"

void ObjectWorld::update(float dt)
{
    ObjectScreen::update(dt);
}

void ObjectWorld::setPosition(const glm::vec2 &position)
{
    position_ = position;
    render_position_ = Game::getInstance().getCurrentScene()->worldToScreen(position_);
}

void ObjectWorld::setRenderPosition(const glm::vec2 &render_position)
{
    render_position_ = render_position;
    position_ = Game::getInstance().getCurrentScene()->screenToWorld(render_position);
}

glm::vec2 ObjectWorld::getRenderPosition()
{
    render_position_ = Game::getInstance().getCurrentScene()->worldToScreen(position_);
    return render_position_;
}
