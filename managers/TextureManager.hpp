#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP
#include <string>
#include <map>
#include <stb/stb_image.h>
#include <GLAD/include/gl.h>


namespace Managers {

class TextureManager {
public:
    static TextureManager* GETINSTANCE();
    unsigned int loadTexture(std::string fileName);
    void activateTexture(unsigned int level,unsigned int id);
private:
    TextureManager();

    std::map<std::string, unsigned int> m_TextureMap;
    static TextureManager* INSTANCE;
};

} // Managers

#endif //TEXTUREMANAGER_HPP
