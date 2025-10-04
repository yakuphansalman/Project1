#ifndef COMPONENT_LIGHT_HPP
#define COMPONENT_LIGHT_HPP
#include <glm/vec3.hpp>

#include "components/Component.hpp"

namespace Managers {
    class Scene;
}

namespace Components {
    class Transform;

    class Light : public Component {
    public:
        Light();

        void bindObject(Objects::Object *object) override;

        const glm::vec3 getColor() const;
        const float getIntensity() const;
        const Transform* getTransform() const;

        void setColor(const glm::vec3& color);
        void setIntensity(const float intensity);
    private:
        glm::vec3 m_Color = glm::vec3(1.0f);
        float m_Intensity = 1.0f;
    };
}




#endif //LIGHT_HPP
