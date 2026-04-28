#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <algorithm>
#include <string>

namespace Objects {
    class Entity;
    class Light;
    class Camera;
    class Object;
}
namespace Components {
    class MeshRenderer;
}
namespace Interface {
    class Gizmos;
}

namespace Managers {
    class Scene {
    public:
        Scene(const std::string name);

        static std::vector<Objects::Object*> OBJECTS;
        static std::vector<Objects::Entity*> ENTITIES;
        static std::vector<Objects::Light*> LIGHTS;
        static std::vector<Objects::Camera*> CAMERAS;
        static std::vector<Components::MeshRenderer*> MESHRENDERERS;
        static Objects::Camera* ACTIVECAMERA;
        static Interface::Gizmos* GIZMOS;
        const static unsigned int MAXLIGHTS = 100;//Fragment Shader stores this data in compile time, so this has to assingn in code


        void setName(const std::string name);
        const std::string getName() const;

        void initScene();

        void erase();
        void erase(const Objects::Entity* entity);
        void erase(const Objects::Light* light);
        void erase(const Objects::Camera* camera);
        void erase(const Components::MeshRenderer* meshRenderer);
    private:
        std::string m_Name;
    };
}





#endif //SCENE_HPP
