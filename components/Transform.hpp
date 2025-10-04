#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Component.hpp"


namespace Components {

    class Transform : public Component {
    public:
        Transform();

        void bindObject(Objects::Object *object) override;

        const glm::vec3 getPosition() const;
        const glm::quat getRotation() const;
        const glm::vec3 getScale() const;
        const glm::vec3 getLocalPosition() const;
        const glm::quat getLocalRotation() const;
        const glm::vec3 getLocalScale() const;
        const glm::mat4 getModel() const;

        void setPosition(const glm::vec3& position);
        void setRotation(const glm::vec3& rotation);
        void setScale(const glm::vec3& scale);
        void setLocalPosition(const glm::vec3& position);
        void setLocalRotation(const glm::vec3& rotation);
        void setLocalScale(const glm::vec3& scale);
    private:
        glm::vec3 m_Position = glm::vec3(0), m_Scale = glm::vec3(1);
        glm::quat m_Rotation = glm::quat();
        glm::mat4 m_Model = glm::mat4(1.0f);

        void updateModel();
    };
}




#endif //TRANSFORM_HPP
