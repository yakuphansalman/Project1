#ifndef MESHRENDERER_HPP
#define MESHRENDERER_HPP
#include <vector>

#include "gl.h"
#include <GLFW/glfw3.h>
#include "programs/ShaderProgram.hpp"
#include "components/Component.hpp"


using namespace Programs;

namespace Managers {
    class Scene;
}
namespace Objects {
    class Object;
}
namespace Interface {
    class Gizmos;
}


namespace Components {
    class MeshRenderer : public Component {
    private:
        struct Vertex {
            glm::vec3 position;
            glm::vec3 normal;
            glm::vec2 texture;
        };
        struct LightData {
            glm::vec3 position;
            int active;
            glm::vec3 color;
            float intensity;
        };
    public:
        MeshRenderer();

        void bindObject(Objects::Object *object) override;

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        static std::vector<glm::vec3> GIZMOSVERTICESX,GIZMOSVERTICESY,GIZMOSVERTICESZ;

        void start();
        void update();
        void stop();
    private:
        static ShaderProgram* M_SHADERPROGRAM;
        static ShaderProgram* M_GIZMOS_SP;
        static LightData LIGHTDATA[];

        unsigned int m_VAO,m_VBO,m_EBO,m_UBO;
        static unsigned int M_G_VAO_X,M_G_VAO_Y,M_G_VAO_Z;
        static unsigned int M_G_VBO_X,M_G_VBO_Y,M_G_VBO_Z;
        bool m_IsStarted = false;

        static void RENDERGIZMOS();
        static void INITGIZMOS();
    };
}




#endif //MESHRENDERER_HPP
