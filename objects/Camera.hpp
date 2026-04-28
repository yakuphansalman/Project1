#ifndef OBJECTS_CAMERA_HPP
#define OBJECTS_CAMERA_HPP

#include "objects/Object.hpp"
#include "components/Camera.hpp"
namespace Objects {
    class Camera : public Object {
    public:
        Camera();
        Camera(const std::string name);

        Components::Camera* getComponent();
    private:
        Components::Camera* m_Camera;
    };
}
#endif //CAMERA_HPP
