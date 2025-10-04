#include "Entity.hpp"
#include "managers/Scene.hpp"
#include "components/MeshRenderer.hpp"
namespace Objects {
    Entity::Entity() {
        m_Type = "entity";
        m_MeshRenderer = new Components::MeshRenderer();
        m_Components.push_back(m_MeshRenderer);
        Managers::Scene::ENTITIES.push_back(this);
    }

}