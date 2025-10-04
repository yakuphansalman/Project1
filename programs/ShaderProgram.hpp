#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include <string>
#include <map>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLAD/include/gl.h>
#include <fstream>
#include <iostream>

namespace Programs {
    class ShaderProgram {
    public:
        ShaderProgram();
        void attachShader(const char* fileName,unsigned int shaderType);
        void link();
        void use();

        void addUniform(const std::string& varName);
        void setInteger(const std::string& varName, int value);
        void setFloat(const std::string& varName, float value);
        void setVec3(const std::string& varName, const glm::vec3& value);
        void setVec4(const std::string& varName, const glm::vec4& value);
        void setMat4(const std::string& varName,const glm::mat4& value);

        void bindBlock(const std::string& varName, unsigned int bindingPoint);
    private:
        unsigned int m_ProgramID;

        std::string getShaderFromFile(const char* fileName);

        std::map<std::string,unsigned int> m_UniformVars;

    };
}





#endif