#include "collider.h"

Collider *Collider::addColliderChild(ObjectScreen *parent, glm::vec2 size, Type collider_type, Anchor anchor)
{
    auto collider = new Collider();
    collider->init();
    collider->setAnchor(anchor);
    collider->setParent(parent);
    collider->setSize(size);
    collider->setColliderType(collider_type);
    if (parent) parent->addChild(collider);
    return collider;
}

void Collider::render()
{
#ifdef DEBUG_MODE
    ObjectAffiliate::render();
    auto pos = parent_->getRenderPosition() + offset_;
    Game::getInstance().renderFillCircle(pos, size_, 0.3);
#endif // DEBUG_MODE
}

bool Collider::isColliding(Collider *other)
{
    if (!other) return false;
    if (collider_type_ == Type::CIRCLE && other->collider_type_ == Type::CIRCLE)      // 两个圆的情况
    {
        auto point1 = parent_->getPosition() + offset_ + size_ / 2.0f;
        auto point2 = other->parent_->getPosition() + other->offset_ + other->size_ / 2.0f;
        return glm::length(point1 - point2) < (size_.x + other->size_.x) / 2.0f;
    }
    // TODO： 其它形状的碰撞检测
    return false;
}
