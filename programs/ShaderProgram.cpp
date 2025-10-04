#include "shaderprogram.hpp"

namespace Programs {
    ShaderProgram::ShaderProgram() {
        m_ProgramID = glCreateProgram();
    }

    void ShaderProgram::link() {
        glLinkProgram(m_ProgramID);
        int isLinked;
        char log[512];
        glGetProgramiv(m_ProgramID,GL_LINK_STATUS, &isLinked);

        if (!isLinked) {
            glGetShaderInfoLog(m_ProgramID, 512, 0, log);
            std::cout << "Program linking error : " << m_ProgramID <<std::endl << log << std::endl;
        }
    }

    void ShaderProgram::use() {
        glUseProgram(m_ProgramID);
    }

    void ShaderProgram::addUniform(const std::string &varName) {
        m_UniformVars[varName] = glGetUniformLocation(m_ProgramID, varName.c_str());
    }

    void ShaderProgram::setInteger(const std::string &varName, int value) {
        glUniform1i(m_UniformVars[varName], value);
    }

    void ShaderProgram::setFloat(const std::string &varName, float value) {
        glUniform1f(m_UniformVars[varName], value);
    }

    void ShaderProgram::setVec3(const std::string &varName, const glm::vec3 &value) {
        glUniform3f(m_UniformVars[varName], value.x, value.y, value.z);
    }

    void ShaderProgram::setVec4(const std::string &varName, const glm::vec4 &value) {
        glUniform4f(m_UniformVars[varName], value.x, value.y, value.z, value.w);
    }

    void ShaderProgram::setMat4(const std::string &varName, const glm::mat4 &value) {
        glUniformMatrix4fv(m_UniformVars[varName], 1,GL_FALSE, &value[0][0]);
    }

    void ShaderProgram::bindBlock(const std::string &blockName, GLuint bindingPoint) {
        GLuint blockIndex = glGetUniformBlockIndex(m_ProgramID, blockName.c_str());
        if (blockIndex == GL_INVALID_INDEX) {
            std::cerr << "UBO Block not found: " << blockName << std::endl;
            return;
        }
        glUniformBlockBinding(m_ProgramID, blockIndex, bindingPoint);
    }

    void ShaderProgram::attachShader(const char *fileName, unsigned int shaderType) {
        unsigned int shaderID = glCreateShader(shaderType);
        std::string sourceCode = getShaderFromFile(fileName);
        const char *ptr_sourceCode = &sourceCode[0];
        glShaderSource(shaderID, 1, &ptr_sourceCode,NULL);
        int isCompiled;
        char log[512];
        glCompileShader(shaderID);
        glGetShaderiv(shaderID,GL_COMPILE_STATUS, &isCompiled);
        glAttachShader(m_ProgramID, shaderID);
        if (!isCompiled) {
            glGetShaderInfoLog(shaderID, 512, 0, log);

            std::cout << "Shader Type : " << shaderType << std::endl << log << std::endl;
        }
    }

    std::string ShaderProgram::getShaderFromFile(const char *fileName) {
        std::fstream file(fileName);

        std::string data;
        if (file.is_open()) {
            char readChar;

            while ((readChar = file.get()) != EOF) {
                data += readChar;
            }
            file.close();
        } else {
            std::cout << "File not found" << std::endl;
        }
        return data;
    }
}
