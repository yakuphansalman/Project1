#include "Transform.hpp"
#include "objects/Object.hpp"

namespace Components {
    Transform::Transform() : m_Position(0.0f), m_Scale(1.0f), m_Rotation(glm::quat(1.0f,0.0f,0.0f,0.0f)){

    }
    void Transform::bindObject(Objects::Object *object) {
        m_Object = object;
        m_Object->getComponents().push_back(this);
        updateModel();
    }


    const glm::vec3 Transform::getPosition() const {
        glm::vec3 position = m_Object->getTransform()->getModel() * glm::vec4(m_Position, 1.0f);
        return glm::vec3(position);
    }

    const glm::quat Transform::getRotation() const {
        glm::vec4 rot = glm::vec4(m_Rotation.x, m_Rotation.y, m_Rotation.z, m_Rotation.w);
        rot = m_Object->getTransform()->getModel() * rot;
        return glm::quat(rot);
    }

    const glm::vec3 Transform::getScale() const {
        glm::vec3 scale = m_Object->getTransform()->getModel() * glm::vec4(m_Scale, 1.0f);
        return glm::vec3(scale);
    }

    const glm::vec3 Transform::getLocalPosition() const {
        return m_Position;
    }

    const glm::quat Transform::getLocalRotation() const {
        return m_Rotation;
    }

    const glm::vec3 Transform::getLocalScale() const {
        return m_Scale;
    }

    const glm::mat4 Transform::getModel() const {
        return m_Model;
    }

    void Transform::setPosition(const glm::vec3 &position) {
        glm::vec4 localPosition = glm::inverse(m_Model) * glm::vec4(position, 1.0f);
        m_Position = glm::vec3(localPosition);
        updateModel();
    }

    void Transform::setRotation(const glm::vec3 &rotation) {
        glm::vec4 rot = glm::inverse(m_Model) * glm::vec4(rotation, 1.0f);
        m_Rotation = glm::quat(rot);
        updateModel();
    }

    void Transform::setScale(const glm::vec3 &scale) {
        glm::vec4 localScale = glm::inverse(m_Model) * glm::vec4(scale, 1.0f);
        m_Scale = glm::vec3(localScale);
        updateModel();
    }

    void Transform::setLocalPosition(const glm::vec3 &position) {
        m_Position = position;
        updateModel();
    }

    void Transform::setLocalRotation(const glm::vec3 &rotation) {
        m_Rotation = rotation;
        updateModel();
    }

    void Transform::setLocalScale(const glm::vec3 &scale) {
        m_Scale = scale;
        updateModel();
    }

    void Transform::updateModel() {
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_Scale);
        glm::mat4 rotationMatrix = glm::mat4_cast(m_Rotation);
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_Position);

        m_Model = translationMatrix * rotationMatrix * scaleMatrix;
    }
}
