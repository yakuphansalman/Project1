#include "TextureManager.hpp"

#include "managers/FileManager.hpp"
namespace Managers {
    TextureManager* TextureManager::INSTANCE = 0;
    TextureManager::TextureManager() {

    }
    TextureManager *TextureManager::GETINSTANCE() {
        if (INSTANCE) return INSTANCE;
        INSTANCE = new TextureManager();
        return INSTANCE;
    }
    unsigned int TextureManager::loadTexture(const std::string fileName) {
        std::string path = TEXTUREFOLDER + fileName;
        unsigned int textureID;
        if (m_TextureMap.count(path) != 0) {
            textureID = m_TextureMap[path];
        }
        else {
            int width, height, nrChannels;
            unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

            stbi_image_free(data);
            m_TextureMap[path] = textureID;
        }
        return textureID;
    }
    void TextureManager::activateTexture(unsigned int level, unsigned int id) {
        glActiveTexture(level);
        glBindTexture(GL_TEXTURE_2D, id);
    }




} // Managers