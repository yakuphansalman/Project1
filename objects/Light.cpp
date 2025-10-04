#include "Light.hpp"
#include "components/Light.hpp"

#include "components/Transform.hpp"
#include "managers/Scene.hpp"

namespace Objects {
    Light::Light() {
        std::cout << "Light Object" << std::endl;
        m_Name = "Light Object";
        m_Type = "light";
        m_Active = false;
        m_Light = new Components::Light();
        m_Light->bindObject(this);
        Managers::Scene::LIGHTS.push_back(this);
    }
    Light::Light(const std::string name) : Light() {
        m_Name = name;
    }
    Components::Light* Light::getComponent() {
        return m_Light;
    }

} // Objects