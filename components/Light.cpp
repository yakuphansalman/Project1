#include "Light.hpp"
#include "Transform.hpp"
#include "objects/Object.hpp"
#include "managers/Scene.hpp"
namespace Components {
    void Light::bindObject(Objects::Object *object) {
        m_Object = object;
        m_Object->getComponents().push_back(this);
    }
    const Transform* Light::getTransform() const {
        return m_Object->getTransform();
    }
    const glm::vec3 Light::getColor() const {
        return m_Color;
    }
    const float Light::getIntensity() const {
        return m_Intensity;
    }
    void Light::setColor(const glm::vec3& color) {
        m_Color = color;
    }
    void Light::setIntensity(const float intensity) {
        m_Intensity = intensity;
    }
}
