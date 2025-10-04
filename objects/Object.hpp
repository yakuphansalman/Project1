#ifndef OBJECT_HPP
#define OBJECT_HPP
#include "objects/Master.hpp"
#include <vector>

namespace Components {
    class Component;
    class Transform;
}

namespace Objects {
    class Object : public Master {
    public:
        Object();

        const std::string& getName() const;
        Components::Transform* getTransform();
        const Components::Transform* getTransform() const;
        const Object* getParent() const;
        const std::vector<Components::Component*> getComponents() const;
        std::vector<Components::Component*> getComponents();

        void setName(const std::string& name);
        void setParent(Object* parent);
        void setParent();

        const std::string toString() const override;
    protected:
        std::string m_Name;
        std::string m_Type;
        Components::Transform* m_Transform;
        Object* m_Parent;
        std::vector<Components::Component*> m_Components;
    private:
        static Object* M_WORLD;
        void initWorld();
    };
}





#endif //OBJECT_HPP
