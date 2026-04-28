#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <fstream>
#include <iostream>
#include <typeinfo>
#include <json/json.hpp>

#include "managers/Scene.hpp"
#include "components/MeshRenderer.hpp"

#define SAVEFOLDER "../saves/"
#define MODELFOLDER "../models/"
#define TEXTUREFOLDER  "../textures/"

using json = nlohmann::json;
using namespace Components;
using namespace Objects;

namespace Managers {
    class FileManager : public Master{
    public:
        static void saveScene(const std::string& fileName);
        static void loadScene(const std::string& fileName);
        static void loadModel(const std::string& fileName, MeshRenderer* meshRenderer);
    private:
    };
}




#endif //FILEMANAGER_HPP
