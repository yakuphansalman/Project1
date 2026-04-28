#include "Scene.hpp"
#include "objects/Entity.hpp"
#include "objects/Light.hpp"
#include "objects/Camera.hpp"
#include "components/MeshRenderer.hpp"
#include "interface/Gizmos.hpp"

namespace Managers {
    std::vector<Objects::Entity *> Scene::ENTITIES;
    std::vector<Objects::Light *> Scene::LIGHTS;
    std::vector<Objects::Camera *> Scene::CAMERAS;
    std::vector<Components::MeshRenderer *> Scene::MESHRENDERERS;
    Objects::Camera *Scene::ACTIVECAMERA;
    Interface::Gizmos *Scene::GIZMOS = new Interface::Gizmos();

    Scene::Scene(const std::string name) {
        std::cout << "Scene initializing" << std::endl;
        m_Name = name;
        initScene();
    }

    const std::string Scene::getName() const {
        return m_Name;
    }

    void Scene::setName(const std::string name) {
        m_Name = name;
    }

    void Scene::initScene() {
        if (LIGHTS.size() == 0) {
            new Objects::Light();
            LIGHTS[0]->setActive(true);
        }
        if (CAMERAS.size() == 0) {
            new Objects::Camera();
            CAMERAS[0]->setActive(true);
            ACTIVECAMERA = CAMERAS[0];
        }
        if (GIZMOS == nullptr) {
            GIZMOS = new Interface::Gizmos();
        }
        std::cout << "Scene initialized successfully" << std::endl;
    }

    void Scene::erase() {
        for (Objects::Entity *e: ENTITIES) delete e;
        ENTITIES.clear();
        for (Objects::Light *l: LIGHTS) delete l;
        LIGHTS.clear();
        ACTIVECAMERA = nullptr;
        for (Objects::Camera *c: CAMERAS) delete c;
        CAMERAS.clear();
    }

    void Scene::erase(const Objects::Entity *entity) {
        const std::string name = entity->getName();
        auto it = std::find(ENTITIES.begin(), ENTITIES.end(), entity);
        ENTITIES.erase(it);
        delete entity;
        std::cout << "Entity : " << name << " removed" << std::endl;
    }

    void Scene::erase(const Objects::Camera *camera) {
        auto it = std::find(CAMERAS.begin(), CAMERAS.end(), camera);
        int index = std::distance(CAMERAS.begin(), it);
        CAMERAS.erase(it);
        delete camera;
        std::cout << "Camera : " << index << " removed" << std::endl;
    }

    void Scene::erase(const Objects::Light *light) {
        auto it = std::find(LIGHTS.begin(), LIGHTS.end(), light);
        int index = std::distance(LIGHTS.begin(), it);
        LIGHTS.erase(it);
        delete light;
        std::cout << "Light : " << index << " removed" << std::endl;
    }
    void Scene::erase(const Components::MeshRenderer *meshRenderer) {
        auto it = std::find(MESHRENDERERS.begin(), MESHRENDERERS.end(), meshRenderer);
        int index = std::distance(MESHRENDERERS.begin(), it);
        MESHRENDERERS.erase(it);
        delete meshRenderer;
        std::cout << "MeshRenderer : " << index << " removed" << std::endl;
    }

}
