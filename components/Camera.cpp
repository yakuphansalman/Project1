#include "Camera.hpp"

#include "managers/Scene.hpp"
#include "components/Transform.hpp"
#include "objects/Object.hpp"

namespace Components {
    Camera::Camera() {
        m_Active = false;
    }
    void Camera::bindObject(Objects::Object *object) {
        m_Object = object;
        m_Object->getComponents().push_back(this);
    }

    const glm::vec3 Camera::getEye() const {
        return m_Eye;
    }

    const glm::vec3 Camera::getCenter() const {
        return m_Center;
    }

    const glm::vec3 Camera::getUp() const {
        return m_Up;
    }

    const glm::mat4 Camera::getView() {
        const Transform *parentTransform = m_Object->getTransform();
        m_Eye = parentTransform->getLocalPosition();
        //center is a normalized forward vector of the camera
        glm::vec3 vecZ = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec4 virtualPosition = parentTransform->getModel() * glm::vec4(vecZ, 1.0f);

        float rotx = cos(parentTransform->getLocalRotation().x) * sin(parentTransform->getLocalRotation().y);
        float roty = sin(parentTransform->getLocalRotation().x);
        float rotz = cos(parentTransform->getLocalRotation().x) * cos(parentTransform->getLocalRotation().y);
        m_Center = glm::vec3(virtualPosition.x,virtualPosition.y,virtualPosition.z);

        glm::vec3 forward = glm::normalize(m_Center - m_Eye);
        glm::vec3 right = glm::normalize(glm::cross(forward, m_Up));
        glm::vec3 up = glm::normalize(glm::cross(right, forward));
        m_Up = up;

        m_View = glm::lookAt(m_Eye, m_Center, m_Up);
        return m_View;
    }

    const glm::mat4 Camera::getProjection() const {
        return m_Projection;
    }
}
