#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <fstream>
#include <iostream>
#include <typeinfo>
#include <json/json.hpp>

#include "managers/Scene.hpp"
#include "objects/Entity.hpp"
#include "objects/Custom.hpp"
#include "components/MeshRenderer.hpp"

using json = nlohmann::json;
using namespace Components;
using namespace Objects;

namespace Managers {
    class FileManager {
    public:
        const static std::string SAVEFOLDER;
        const static std::string MODELFOLDER;

        static void saveScene(const std::string& fileName);
        static void loadScene(const std::string& fileName);
        static void loadModel(const std::string& fileName, MeshRenderer* meshRenderer);
    private:
        static json entityToJson(const Entity* entity);
        static Entity* jsonToEntity(const json& j);

        static json componentToJson(const Component* component);
        static Component* jsonToComponent(const json& j);
    };
}




#endif //FILEMANAGER_HPP
