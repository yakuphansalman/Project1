#include "Object.hpp"
#include "components/Transform.hpp"
namespace Objects {
    Object *Object::M_WORLD = new Object();

    Object::Object() {
        m_Name = "Object";
        m_Type = "object";
        m_Transform = new Components::Transform();
        m_Transform->bindObject(this);
        initWorld();
        if (this != M_WORLD) setParent(M_WORLD);
    }

    const std::string &Object::getName() const {
        return m_Name;
    }
    Components::Transform *Object::getTransform() {
        return m_Transform;
    }
    const Components::Transform *Object::getTransform() const {
        return m_Transform;
    }
    const Object *Object::getParent() const {
        return m_Parent;
    }
    const std::vector<Components::Component*> Object::getComponents() const {
        return m_Components;
    }
    std::vector<Components::Component*> Object::getComponents() {
        return m_Components;
    }
    const bool Object::isActive() const {
        return m_Active;
    }

    const std::string Object::getType() const {
        return m_Type;
    }


    void Object::setActive(bool active) {
        m_Active = active;
    }
    void Object::setName(const std::string &name) {
        m_Name = name;
    }
    void Object::setParent(Object *parent) {
        m_Parent = parent;
    }
    void Object::setParent() {
        m_Parent = M_WORLD;
    }

    void Object::initWorld() {
        static bool *once = new bool;
        *once = true;
        if (M_WORLD != nullptr && *once) {
            M_WORLD->setName("World");
            *once = false;
        }
        if (!once) delete once;
    }

    const std::string Object::toString() const {
        oss << "Object : " << m_Name << std::endl
                << "Parent : " << m_Parent->getName() << std::endl;
        return oss.str();
    }
}
