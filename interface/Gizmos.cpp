#include "Gizmos.hpp"

#include "components/Transform.hpp"
#include "managers/Scene.hpp"
#include "objects/Camera.hpp"

namespace Interface {
    Objects::Object* Gizmos::PARENT;

    const glm::mat4 Gizmos::GETMODEL() {
        if (PARENT == nullptr) PARENT = new Objects::Object();
        glm::mat4 model = glm::mat4(1.0f);
        glm::vec3 camPos = Managers::Scene::ACTIVECAMERA->getTransform()->getLocalPosition();
        glm::vec3 parentPos = PARENT->getTransform()->getLocalPosition();
        float distance = glm::length(camPos - parentPos);
        float scale = distance * 0.1f;
        model = glm::translate(glm::mat4(1.0f),parentPos);
        model = glm::scale(model,glm::vec3(scale));
        return model;
    }
    const glm::vec3 Gizmos::GETCOLOR() {
        if (PARENT == nullptr) PARENT = new Objects::Object();
        static float ang = 0.0f;
        if (ang >= 6) ang = 0.0f;//This angle is between 240 and 360
        float x = cos(ang) > 0.0f ? 1.0f : 0.0f;
        float y= cos(ang + 4*M_PI/3) > 0.0f ? 1.0f : 0.0f;
        float z = cos(ang + 2*M_PI/3) > 0.0f ? 1.0f : 0.0f;
        glm::vec3 color = glm::vec3(x,y,z);
        ang += 2*M_PI/3;
        return color;
    }

} // Interface