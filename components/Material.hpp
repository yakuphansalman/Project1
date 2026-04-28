#ifndef MATERIAL_HPP
#define MATERIAL_HPP


#include "Component.hpp"

namespace Components {

class Material : public Component{
private:
    unsigned int texture;
public:
    void setTexture(std::string path);
    void updateTexture();
};

} // Components

#endif //MATERIAL_HPP
