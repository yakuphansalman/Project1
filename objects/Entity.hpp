#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Object.hpp"

namespace Components {
    class MeshRenderer;
}

namespace Objects {
    class Entity : public Object {
    protected:
        Entity();
        Components::MeshRenderer* m_MeshRenderer;
    };
}

#endif //ENTITY_HPP
