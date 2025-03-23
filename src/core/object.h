#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"
#include "defs.h"
#include <vector>

class Object {
    
protected:
    ObjectType type_ = ObjectType::NONE;
    std::vector<Object*> object_to_add_;
    std::vector<Object*> children_;
    bool is_active_ = true;
    bool need_remove_ = false;
public:
    Object() = default;
    virtual ~Object() = default;    // 所有的类，不在构造函数和析构函数里面做任何事。

    virtual void init() {}      // 需要初始化的事物，在init()函数里面做。
    virtual bool handleEvents(SDL_Event& event);        // 处理事件: 事件如果被处理，则返回真，否则继续向下传递（每次传递的时候检查是否已被处理）
    virtual void update(float dt);
    virtual void render();
    virtual void clean();   // 需要清理的资源，在clean()函数里面做。

    void safeAddChild(Object* child) { object_to_add_.push_back(child); }
    virtual void addChild(Object* child) { children_.push_back(child); }
    virtual void removeChild(Object* child) {
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
    }
    

    // getters and setters
    ObjectType getType() const { return type_; }
    void setType(ObjectType type) { type_ = type; }
    void setActive(bool active) { is_active_ = active; }
    bool getActive() const { return is_active_; }
    bool getNeedRemove() const { return need_remove_; }
    void setNeedRemove(bool need_remove) { need_remove_ = need_remove; }
};



#endif // OBJECT_H