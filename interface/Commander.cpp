#include "../interface/Commander.hpp"

#include <vector>

#include "Gizmos.hpp"
#include "components/Transform.hpp"
#include "managers/Scene.hpp"
#include "objects/Camera.hpp"
#include "objects/Custom.hpp"
#include "objects/Entity.hpp"
#include "objects/Light.hpp"

Commander::Commander() {
    m_Thread = std::thread(&Commander::command, this);
}
Commander::~Commander() {
    m_Running = false;
    if (m_Thread.joinable()) m_Thread.join();
}
bool Commander::isRunning() {
    return m_Running;
}





void Commander::command() {
    AllocConsole();
    freopen("CONOUT$","w",stdout);
    freopen("CONIN$","r",stdin);
    std::string input;

    unsigned int index = 0;
    std::string curr;
    while (m_Running) {
        std::cout << "\nCMD > ";
        std::getline(std::cin,input);
        if (input == "exit") {
            m_Running = false;
            break;
        }
        if (input.empty()) continue;

        std::istringstream iss(input);
        std::vector<std::string> tokens;
        std::string token;

        while (iss >> token) tokens.push_back(token);
        if (token.empty()) continue;
        if (tokens[0] == "sel") {
            if (tokens.size() != 3) continue;
            index = std::stoi(tokens[2]);
            curr = tokens[1];
            if (tokens[1] == "ent") {
                if (index >= Managers::Scene::ENTITIES.size() || Managers::Scene::ENTITIES[index] == nullptr)
                    std::cout << "There's no entity in the scene" << std::endl;
                else {
                    std::cout << "Selected object " << index << " : " << Managers::Scene::ENTITIES[index]->getName() << std::endl;
                    Interface::Gizmos::PARENT = Managers::Scene::ENTITIES[index];
                }

            }
            if (tokens[1] == "lig") {
                if (index >= Managers::Scene::LIGHTS.size() || Managers::Scene::LIGHTS[index] == nullptr)
                    std::cout << "There's no light in the scene" << std::endl;
                else {
                    std::cout << "Selected light " << index << " : " << Managers::Scene::LIGHTS[index]->getName() << std::endl;
                    Interface::Gizmos::PARENT = Managers::Scene::LIGHTS[index];
                }
            }
            if (tokens[1] == "cam") {
                if (index >= Managers::Scene::CAMERAS.size() || Managers::Scene::CAMERAS[index] == nullptr)
                    std::cout << "There's no camera in the scene" << std::endl;
                else {
                    std::cout << "Selected camera " << index << " : " << Managers::Scene::CAMERAS[index]->getName() << std::endl;
                }

            }
        }
        if (tokens[0] == "cre") {
            curr = tokens[1];
            if (tokens[1] == "cus") {
                new Objects::Custom(tokens[2]);
                std::cout << "A custom object has created : " << tokens[2] << std::endl;
            }
            else if (tokens[1] == "lig") {
                new Objects::Light();
                std::cout << "A light object has created" << std::endl;
            }
            else if (tokens[1] == "cam") {
                new Objects::Camera();
                std::cout << "A camera object has created" << std::endl;
            }
        }
        if (tokens[0] == "act") {
            if (tokens.size() != 2 ) continue;
            unsigned int index = std::stoi(tokens[1]);
            if (curr == "ent" && Managers::Scene::ENTITIES[index] != nullptr ) {
                if (Managers::Scene::ENTITIES[index]->isActive()) {
                    std::cout << "Entity : " << Managers::Scene::ENTITIES[index]->getName() << " is already active" <<  std::endl;
                    continue;
                }
                Managers::Scene::ENTITIES[index]->setActive(true);
                std::cout << "Entity : " << Managers::Scene::ENTITIES[index]->getName() << " has activated" << std::endl;
            }
            else if (curr == "lig" && Managers::Scene::LIGHTS[index] != nullptr) {
                if (Managers::Scene::LIGHTS[index]->isActive()) {
                    std::cout << "Light : " << Managers::Scene::LIGHTS[index]->getName() << " is already active" << std::endl;
                    continue;
                }
                Managers::Scene::LIGHTS[index]->setActive(true);
                std::cout << "Light[" << index << "] has activated" << std::endl;
            }
            else if (curr == "cam" && Managers::Scene::CAMERAS[index] != nullptr) {
                if (Managers::Scene::CAMERAS[index]->isActive()) {
                    std::cout << "Camera : " << Managers::Scene::CAMERAS[index]->getName() << " is already active" << std::endl;
                    continue;
                }
                Managers::Scene::ACTIVECAMERA->setActive(false);
                Managers::Scene::CAMERAS[index]->setActive(true);
                Managers::Scene::ACTIVECAMERA = Managers::Scene::CAMERAS[index];
                std::cout << "Camera[" << index << "] has activated" << std::endl;
            }
        }
        if (tokens[0] == "tra") {
            Components::Transform* tra;
            if (curr == "ent")
                tra = Managers::Scene::ENTITIES[index]->getTransform();
            else if (curr == "lig")
                tra = Managers::Scene::LIGHTS[index]->getTransform();
            else if (curr == "cam")
                tra = Managers::Scene::CAMERAS[index]->getTransform();
            else {
                std::cout << "There's no transform for that type" << std::endl;
                continue;
            }
            if (tokens[1] == "set") {
                if (tokens.size() != 6) {
                    continue;
                }
                float x = std::stof(tokens[3]), y = std::stof(tokens[4]), z = std::stof(tokens[5]);
                if (tokens[2] == "pos") {
                    tra->setPosition(glm::vec3(x,y,z));
                    std::cout << "Position set" << std::endl;
                }
                else if (tokens[2] == "rot") {
                    tra->setRotation(glm::vec3(x,y,z));
                    std::cout << "Rotation set" << std::endl;
                }
                else if (tokens[2] == "sca") {
                    tra->setScale(glm::vec3(x,y,z));
                    std::cout << "Scale set" << std::endl;
                }
                else if (tokens[2] == "lpos") {
                    tra->setLocalPosition(glm::vec3(x,y,z));
                    std::cout << "Local Position set" << std::endl;
                }
                else if (tokens[2] == "lrot") {
                    tra->setLocalRotation(glm::vec3(x,y,z));
                    std::cout << "Local Rotation set" << std::endl;
                }
                else if (tokens[2] == "lsca") {
                    tra->setLocalScale(glm::vec3(x,y,z));
                    std::cout << "Local Scale set" << std::endl;
                }
            }
            if (tokens[1] == "log") {
                if (tokens.size() != 3) {
                    std::cout << "Wrong parameters" << std::endl;
                    continue;
                }
                if (tokens[2] == "mat") {
                    std::cout << "MATRIX LOG " << std::endl;
                    for (int i = 0;i<4;i++) {
                        for (int j=0;j<4;j++) {
                            std::cout << glm::transpose(tra->getModel())[i][j] << "\t";
                        }
                        std::cout << std::endl;
                    }
                }
                if (tokens[2] == "cent") {
                    std::cout << Managers::Scene::ACTIVECAMERA->getComponent()->getCenter().x  <<"," << Managers::Scene::ACTIVECAMERA->getComponent()->getCenter().y << "," << Managers::Scene::ACTIVECAMERA->getComponent()->getCenter().z << std::endl;
                }
                if (tokens[2] == "col") {
                    std::cout << Interface::Gizmos::GETCOLOR().x << "," << Interface::Gizmos::GETCOLOR().y << "," << Interface::Gizmos::GETCOLOR().z << std::endl;
                    Interface::Gizmos::GETCOLOR();
                }
            }
        }
        if (tokens[0] == "giz") {
            if (tokens[1] == "loc") {
                Interface::Gizmos::ISGLOBAL = false;
                std::cout << "Gizmo localized" << std::endl;
            }
            else if (tokens[1] == "glo") {
                Interface::Gizmos::ISGLOBAL = true;
                std::cout << "Gizmo global" << std::endl;
            }
        }
        if (tokens[0] == "tex") {
            if (tokens.size() == 3) {
                try {
                    int i = std::stoi(tokens[1]);
                    std::string textureName = tokens[2];

                    {
                        std::lock_guard<std::mutex> lock(g_CommandMutex);
                        g_CommandQueue.push([i,textureName]() {
                           if (i< Managers::Scene::ENTITIES.size()) {
                               Managers::Scene::ENTITIES[i]->getMaterial()->setTexture("texture_0.jpg");
                               std::cout << "Texture : " << textureName << " attached to " << Managers::Scene::ENTITIES[i]->getName() << std::endl;
                           }
                        });
                    }
                } catch (const std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            }
            else {
                std::cout << "Wrong parameters" << std::endl;
            }
        }
        if (tokens[0] == "file") {
            if (tokens[1] == "save") {
                if (tokens.size() != 3) {
                    std::cout << "Wrong parameters!" << std::endl;
                    continue;
                }
                FileManager::saveScene(tokens[2]);
            }
        }
    }
    FreeConsole();
}
