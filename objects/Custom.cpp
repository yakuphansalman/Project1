#include "Custom.hpp"
#include "components/Transform.hpp"



namespace Objects {
    Custom::Custom(const std::string fileName) : Entity(){
        std::cout << "Custom Object : " << fileName << " has created"<<std::endl;
        m_Name = fileName;
        m_Type = "custom";
        m_FileName = fileName;
        m_Transform->bindObject(this);
        FileManager::loadModel(fileName,m_MeshRenderer);
        m_MeshRenderer->bindObject(this);
    }
    const std::string Custom::getFileName() const {
        return m_FileName;
    }
}

