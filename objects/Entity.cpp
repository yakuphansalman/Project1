#include "Entity.hpp"
#include "managers/Scene.hpp"
#include "components/MeshRenderer.hpp"
namespace Objects {
    Entity::Entity() {
        m_Type = "entity";
        m_MeshRenderer = new Components::MeshRenderer();
        m_Material = new Components::Material();
        m_Components.push_back(m_MeshRenderer);
        Managers::Scene::ENTITIES.push_back(this);
    }
    Components::Material *Entity::getMaterial() {
        return m_Material;
    }


}