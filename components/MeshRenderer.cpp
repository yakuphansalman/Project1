#include "MeshRenderer.hpp"

#include "Transform.hpp"
#include "interface/Gizmos.hpp"
#include "managers/Scene.hpp"
#include "objects/Object.hpp"
#include "objects/Light.hpp"
#include "objects/Camera.hpp"

namespace Components {
    ShaderProgram *MeshRenderer::M_SHADERPROGRAM;
    ShaderProgram *MeshRenderer::M_GIZMOS_SP;
    MeshRenderer::LightData MeshRenderer::LIGHTDATA[Managers::Scene::MAXLIGHTS];
    unsigned int MeshRenderer::M_G_VAO_X,MeshRenderer::M_G_VAO_Y,MeshRenderer::M_G_VAO_Z;
    unsigned int MeshRenderer::M_G_VBO_X,MeshRenderer::M_G_VBO_Y,MeshRenderer::M_G_VBO_Z;
    std::vector<glm::vec3> MeshRenderer::GIZMOSVERTICESX,MeshRenderer::GIZMOSVERTICESY,MeshRenderer::GIZMOSVERTICESZ;


    MeshRenderer::MeshRenderer() {
        Managers::Scene::MESHRENDERERS.push_back(this);
    }

    void MeshRenderer::bindObject(Objects::Object *object) {
        m_Object = object;
        m_Object->getComponents().push_back(this);
    }

    void MeshRenderer::start() {
        if (!m_Active) return;
        if (M_SHADERPROGRAM == nullptr) M_SHADERPROGRAM = new ShaderProgram();
        if (M_GIZMOS_SP == nullptr) M_GIZMOS_SP = new ShaderProgram();

        printf("MeshRenderer initialized!\n");
        static bool init = false;
        /*
        std::cout << "VERTICES" << std::endl;
        for (int i = 0; i < vertices.size(); i++) {
            std::cout << "[" << i << "]" << std::endl;
            std::cout << "Position : " << "\t x : " << vertices[i].position.x << "\t y : " << vertices[i].position.y <<
                    "\t z : " << vertices[i].position.z << std::endl;
            std::cout << "Normal : " << "\t x : " << vertices[i].normal.x << "\t y : " << vertices[i].normal.y <<
                    "\t z : " << vertices[i].normal.z << std::endl;
            std::cout << "Texture : " << "\t x : " << vertices[i].texture.x << "\t y : " << vertices[i].texture.y <<
                    std::endl;
            std::cout << std::endl;
        }
        std::cout << "INDICES" << std::endl;
        for (int i = 0; i < indices.size(); i++) {
            if (i % 3 == 0) std::cout << std::endl;
            std::cout << "Index [" << i << "] : " << indices[i] << "\t";
        }
        */
        if (!init) {
            LIGHTDATA[Managers::Scene::MAXLIGHTS] = {};
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            M_SHADERPROGRAM->attachShader("../shaders/vertex.glsl",GL_VERTEX_SHADER);
            M_SHADERPROGRAM->attachShader("../shaders/fragment.glsl",GL_FRAGMENT_SHADER);
            M_SHADERPROGRAM->link();
            M_SHADERPROGRAM->addUniform("uLightCount");
            M_SHADERPROGRAM->addUniform("uLightPos");
            M_SHADERPROGRAM->addUniform("uLightColor");
            M_SHADERPROGRAM->addUniform("uEye");
            M_SHADERPROGRAM->addUniform("uProjection");
            M_SHADERPROGRAM->addUniform("uView");
            M_SHADERPROGRAM->addUniform("uModel");
            M_SHADERPROGRAM->addUniform("uColor");

            INITGIZMOS();
            init = true;
        }

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
        glGenBuffers(1, &m_UBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(),GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(),GL_STATIC_DRAW);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(LightData) * Managers::Scene::MAXLIGHTS, nullptr,GL_STATIC_DRAW);

        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightData) * Managers::Scene::MAXLIGHTS, LIGHTDATA);

        M_SHADERPROGRAM->bindBlock("LightBlock", 0);

        glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_UBO);
        size_t offset = 0;
        glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE, sizeof(Vertex), (void *) offset);
        glEnableVertexAttribArray(0);
        offset += sizeof(glm::vec3);
        glVertexAttribPointer(1, 3,GL_FLOAT,GL_FALSE, sizeof(Vertex), (void *) offset);
        glEnableVertexAttribArray(1);
        offset += sizeof(glm::vec3);
        glVertexAttribPointer(2, 2,GL_FLOAT,GL_FALSE, sizeof(Vertex), (void *) offset);
        glEnableVertexAttribArray(2);



        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBindVertexArray(0);



        m_IsStarted = true;
        std::cout << "\nMeshRenderer started : " << m_Object->getName() << std::endl;
    }

    void MeshRenderer::update() {
        if (!m_Active) return;
        if (!m_IsStarted) start();
        M_SHADERPROGRAM->use();

        if (Managers::Scene::ACTIVECAMERA == nullptr) {
            std::cout << "Active Camera couldnt found" << std::endl;
        }

        M_SHADERPROGRAM->setInteger("uLightCount", Managers::Scene::LIGHTS.size());
        M_SHADERPROGRAM->setVec3("uEye", Managers::Scene::ACTIVECAMERA->getComponent()->getEye());
        M_SHADERPROGRAM->setMat4("uProjection", Managers::Scene::ACTIVECAMERA->getComponent()->getProjection());
        M_SHADERPROGRAM->setMat4("uView", Managers::Scene::ACTIVECAMERA->getComponent()->getView());
        M_SHADERPROGRAM->setMat4("uModel", m_Object->getTransform()->getModel());
        M_SHADERPROGRAM->setVec4("uColor",glm::vec4(0.75f, 0.75f, 0.75f, 1.0f));


        /* Light data update */
        for (int i = 0; i < Managers::Scene::LIGHTS.size(); i++) {
            LIGHTDATA[i].position = Managers::Scene::LIGHTS[i]->getTransform()->getPosition();
            LIGHTDATA[i].active = Managers::Scene::LIGHTS[i]->isActive();
            LIGHTDATA[i].color = Managers::Scene::LIGHTS[i]->getComponent()->getColor();
            LIGHTDATA[i].intensity = Managers::Scene::LIGHTS[i]->getComponent()->getIntensity();

        }

        glBindVertexArray(m_VAO);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightData) * Managers::Scene::MAXLIGHTS, LIGHTDATA);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glDrawElements(GL_TRIANGLES, indices.size(),GL_UNSIGNED_INT, 0);

        RENDERGIZMOS();
    }

    void MeshRenderer::stop() {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
        glDeleteBuffers(1, &m_UBO);
        m_Active = false;
    }

    void MeshRenderer::INITGIZMOS() {
        float ws = 0.05f, wt = 0.3f, hs = 3.0f;
        int freq = 10;
        if (GIZMOSVERTICESX.size() == 0) {
            GIZMOSVERTICESX  = {
                {0.0f,ws,0.0f},
                {0.0f,-ws,0.0f},
                {hs,ws,0.0f},
                {hs,ws,0.0f},
                {0.0f,-ws,0.0f},
                {hs,-ws,0.0f},
                {0.0f,0.0f,ws},
                {0.0f,0.0f,-ws},
                {hs,0.0f,ws},
                {hs,0.0f,ws},
                {hs,0.0f,-ws},
                {0.0f,0.0f,-ws},
            };
        }
        for (int i = 0;i< freq;i++) {
            GIZMOSVERTICESX.push_back(glm::vec3(hs,0,0));
            GIZMOSVERTICESX.push_back(glm::vec3(hs,wt*sin(2*M_PI*i/freq),wt*cos(2*M_PI*i/freq)));
            GIZMOSVERTICESX.push_back(glm::vec3(hs,wt*sin(2*M_PI*(i+1)/freq),wt*cos(2*M_PI*(i+1)/freq)));
            GIZMOSVERTICESX.push_back(glm::vec3(hs,wt*sin(2*M_PI*i/freq),wt*cos(2*M_PI*i/freq)));
            GIZMOSVERTICESX.push_back(glm::vec3(hs,wt*sin(2*M_PI*(i+1)/freq),wt*cos(2*M_PI*(i+1)/freq)));
            GIZMOSVERTICESX.push_back(glm::vec3(hs + wt,0,0));
        }
        for (auto& v : GIZMOSVERTICESX) {
            GIZMOSVERTICESY.push_back(glm::vec3(v.y,v.x,v.z));
            GIZMOSVERTICESZ.push_back(glm::vec3(v.y,v.z,v.x));
        }

        M_GIZMOS_SP->attachShader("../shaders/gizmos_vertex.glsl",GL_VERTEX_SHADER);
        M_GIZMOS_SP->attachShader("../shaders/gizmos_fragment.glsl",GL_FRAGMENT_SHADER);
        M_GIZMOS_SP->link();
        M_GIZMOS_SP->addUniform("uModel");
        M_GIZMOS_SP->addUniform("uProjection");
        M_GIZMOS_SP->addUniform("uView");
        M_GIZMOS_SP->addUniform("uColor");

        glGenVertexArrays(1, &M_G_VAO_X);
        glBindVertexArray(M_G_VAO_X);
        glGenBuffers(1, &M_G_VBO_X);
        glBindBuffer(GL_ARRAY_BUFFER, M_G_VBO_X);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * GIZMOSVERTICESX.size(), GIZMOSVERTICESX.data(),GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE, sizeof(glm::vec3), (void *) 0);
        glEnableVertexAttribArray(0);

        glGenVertexArrays(1, &M_G_VAO_Y);
        glBindVertexArray(M_G_VAO_Y);
        glGenBuffers(1, &M_G_VBO_Y);
        glBindBuffer(GL_ARRAY_BUFFER, M_G_VBO_Y);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * GIZMOSVERTICESY.size(), GIZMOSVERTICESY.data(),GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE, sizeof(glm::vec3), (void *) 0);
        glEnableVertexAttribArray(0);

        glGenVertexArrays(1, &M_G_VAO_Z);
        glBindVertexArray(M_G_VAO_Z);
        glGenBuffers(1, &M_G_VBO_Z);
        glBindBuffer(GL_ARRAY_BUFFER, M_G_VBO_Z);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * GIZMOSVERTICESZ.size(), GIZMOSVERTICESZ.data(),GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE, sizeof(glm::vec3), (void *) 0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }


    void MeshRenderer::RENDERGIZMOS() {
        glDisable(GL_DEPTH_TEST);
        M_GIZMOS_SP->use();
        M_GIZMOS_SP->setMat4("uModel", Interface::Gizmos::GETMODEL());
        M_GIZMOS_SP->setMat4("uProjection",Managers::Scene::ACTIVECAMERA->getComponent()->getProjection());
        M_GIZMOS_SP->setMat4("uView",Managers::Scene::ACTIVECAMERA->getComponent()->getView());
        M_GIZMOS_SP->setVec3("uColor", Interface::Gizmos::GETCOLOR());
        glBindVertexArray(M_G_VAO_X);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, GIZMOSVERTICESX.size());
        M_GIZMOS_SP->setVec3("uColor", Interface::Gizmos::GETCOLOR());
        glBindVertexArray(M_G_VAO_Y);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES,0,GIZMOSVERTICESY.size());
        M_GIZMOS_SP->setVec3("uColor", Interface::Gizmos::GETCOLOR());
        glBindVertexArray(M_G_VAO_Z);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES,0,GIZMOSVERTICESZ.size());
        glBindVertexArray(0);
        glEnable(GL_DEPTH_TEST);
    }
}
