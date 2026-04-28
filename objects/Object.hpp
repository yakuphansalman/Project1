#ifndef OBJECT_HPP
#define OBJECT_HPP
#include "../Master.hpp"
#include <vector>

#include "components/Component.hpp"

namespace Components {
    class Component;
    class Transform;
}

namespace Objects {
    class Object : public Master {
        REFLECTABLE_CLASS(Generated)
    public:
        Object();

        const std::string& getName() const;
        Components::Transform* getTransform();
        const Components::Transform* getTransform() const;
        const Object* getParent() const;
        const std::vector<Components::Component*> getComponents() const;
        std::vector<Components::Component*> getComponents();
        const bool isActive() const;
        const std::string getType() const;

        template<typename T> T* getComponent(int index) {
            Components::Component* baseComp = m_Components[index];
            return dynamic_cast<T*>(baseComp);
        }

        void setActive(bool active);
        void setName(const std::string& name);
        void setParent(Object* parent);
        void setParent();

        template<typename T> int addComponent() {
            T* newComponent = new T;
            m_Components.push_back(newComponent);
            return m_Components.size() - 1;
        }

        const std::string toString() const override;
    protected:
        std::string m_Name;
        bool m_Active = true;
        std::string m_Type;
        PROPERTY(SAVE)
        Components::Transform* m_Transform;
        Object* m_Parent;
        std::vector<Components::Component*> m_Components;
    private:
        static Object* M_WORLD;
        void initWorld();
    };
}





#endif //OBJECT_HPP
