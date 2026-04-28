#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Object.hpp"
#include "components/Material.hpp"

namespace Components {
    class MeshRenderer;
}

namespace Objects {
    class Entity : public Object {
    protected:
        Entity();
        Components::MeshRenderer* m_MeshRenderer;
        Components::Material* m_Material;
    public:
        Components::Material* getMaterial();
    };
}

#endif //ENTITY_HPP
