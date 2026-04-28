#include "Material.hpp"

#include "managers/TextureManager.hpp"

namespace Components {
    void Material::setTexture(std::string fileName) {
        texture = Managers::TextureManager::GETINSTANCE()->loadTexture(fileName);
    }
    void Material::updateTexture() {
        if (texture) return;
        Managers::TextureManager::GETINSTANCE()->activateTexture(GL_TEXTURE0,texture);
    }
} // Components