#ifndef COMPONENTS_CAMERA_HPP
#define COMPONENTS_CAMERA_HPP

#include "components/Component.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Managers {
    class Scene;
}

namespace Components {
    class Camera : public Component {
    public:
        void bindObject(Objects::Object *object) override;

        const glm::vec3 getEye() const;
        const glm::vec3 getCenter() const;
        const glm::vec3 getUp() const;

        const glm::mat4 getView();
        const glm::mat4 getProjection() const;
    private:
        glm::vec3 m_Eye = glm::vec3(0.0f,1.0f,2.0f);
        glm::vec3 m_Center = glm::vec3(0);
        glm::vec3 m_Up = glm::vec3(0,1,0);

        glm::mat4 m_View = glm::lookAt(m_Eye,m_Center,m_Up);
        glm::mat4 m_Projection = glm::perspective<float>(glm::radians(90.0f),1.0f,1.0f,100.0f);

        void updateVectors();
    };
}




#endif //CAMERA_HPP
