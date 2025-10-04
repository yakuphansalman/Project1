#ifndef CUSTOM_HPP
#define CUSTOM_HPP

#include "objects/Entity.hpp"
#include "managers/FileManager.hpp"


using namespace Managers;

namespace Objects {
    class Custom : public Entity {
    public:
        Custom(const std::string fileName);
        const std::string getFileName() const;
    private:
        std::string m_FileName;
    };
}




#endif //CUSTOM_HPP
