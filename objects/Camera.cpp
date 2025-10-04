#include "Camera.hpp"
#include "managers/Scene.hpp"
namespace Objects {
    Camera::Camera() {
        std::cout << "Camera Object" << std::endl;
        m_Name = "Camera Object";
        m_Type = "camera";
        m_Camera = new Components::Camera();
        m_Camera->bindObject(this);
        Managers::Scene::CAMERAS.push_back(this);
    }
    Camera::Camera(const std::string name) : Camera() {
        m_Name = name;
    }
    Components::Camera* Camera::getComponent() {
        return m_Camera;
    }


}
