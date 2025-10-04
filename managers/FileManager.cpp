#include "FileManager.hpp"

namespace Managers {
    const std::string FileManager::SAVEFOLDER = "../saves/";
    const std::string FileManager::MODELFOLDER = "../models/";

    void FileManager::saveScene(const std::string &fileName) {
    }

    void FileManager::loadScene(const std::string &fileName) {
    }

    void FileManager::loadModel(const std::string &fileName, MeshRenderer *meshRenderer) {
        const std::string path = MODELFOLDER + fileName + ".obj";
        std::vector<unsigned int> vertexIndices,uvIndices,normalIndices;
        std::vector<glm::vec3> temp_v;
        std::vector<glm::vec2> temp_uv;
        std::vector<glm::vec3> temp_n;
        FILE* file = fopen(path.c_str(), "r");
        if (file == NULL) {
            std::cout << "File not found : " << path << std::endl;
            return;
        }
        while (1) {
            char lineHeader[128];
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF) break;
            if (strcmp(lineHeader, "v") == 0) {
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                temp_v.push_back(vertex);
            }
            else if (strcmp(lineHeader, "vn") == 0) {
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y,&normal.z);
                temp_n.push_back(normal);
            }
            else if (strcmp(lineHeader, "vt") == 0) {
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y);
                temp_uv.push_back(uv);
            }
            else if (strcmp(lineHeader, "f") == 0) {
                std::string vertex1, vertex2, vertex3;
                unsigned int vIdx[3], uvIdx[3], nIdx[3];
                int matches = fscanf(file,"%d/%d/%d %d/%d/%d %d/%d/%d\n",&vIdx[0],&uvIdx[0],&nIdx[0],&vIdx[1],&uvIdx[1],&nIdx[1],&vIdx[2],&uvIdx[2],&nIdx[2]);
                if (matches != 9) {
                    std::cout << "Try triangulate the object" << std::endl;
                    return;
                }
                vertexIndices.push_back(vIdx[0]);
                vertexIndices.push_back(vIdx[1]);
                vertexIndices.push_back(vIdx[2]);
                uvIndices.push_back(uvIdx[0]);
                uvIndices.push_back(uvIdx[1]);
                uvIndices.push_back(uvIdx[2]);
                normalIndices.push_back(nIdx[0]);
                normalIndices.push_back(nIdx[1]);
                normalIndices.push_back(nIdx[2]);
            }
        }
        meshRenderer->vertices.resize(vertexIndices.size());
        for (int i = 0;i<temp_v.size();i++) {
            meshRenderer->vertices[i].position = temp_v[i];
        }
        for (int i = 0;i<vertexIndices.size();i++) {
            meshRenderer->indices.push_back(vertexIndices[i]-1);
            meshRenderer->vertices[i].normal = temp_n[normalIndices[i]-1];
            meshRenderer->vertices[i].texture = temp_uv[uvIndices[i]-1];
        }
    }

    json FileManager::entityToJson(const Entity *entity) {
        return nullptr;
    }

    Entity *FileManager::jsonToEntity(const json &j) {
        return nullptr;
    }

    json FileManager::componentToJson(const Component *component) {
        return nullptr;
    }

    Component *FileManager::jsonToComponent(const json &j) {
        return nullptr;
    }
}
