#include <iostream>
#include <GLAD/include/gl.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <windows.h>
#define STB_IMAGE_IMPLEMENTATION

#include "interface/Commander.hpp"
#include "managers/Scene.hpp"
#include "objects/Custom.hpp"
#include "components/MeshRenderer.hpp"
#include "components/Transform.hpp"
#include "interface/Gizmos.hpp"
#include "managers/Time.hpp"
#include "objects/Camera.hpp"
#include "objects/Light.hpp"


Managers::Scene* scene = new Managers::Scene("main scene");
//Objects::Custom* custom = new Objects::Custom("cube-updated");
Managers::Time* timer = new Managers::Time();
float ang = 0.0f;
float radius = 3.0f;
void start() {
    Scene::ACTIVECAMERA->getTransform()->setLocalPosition(glm::vec3(0.0f, 1.0f, 3.0f));
    Scene::ACTIVECAMERA->getTransform()->setLocalRotation(glm::vec3(-0.1f, 0.0f, 0.0f));
    Scene::LIGHTS[0]->getTransform()->setLocalPosition(glm::vec3(0.0f, 3.0f, 0.0f));
    for (auto* renderer : Managers::Scene::MESHRENDERERS) {
        renderer->start();
    }
}
void update() {
    ang+= 0.008f;
    glm::vec3 route = glm::vec3(cos(ang),1.0f,sin(ang)) * radius;
    Scene::LIGHTS[0]->getTransform()->setLocalPosition(route);
    //custom->getTransform()->setLocalRotation(glm::vec3(ang));
    for (auto* renderer : Managers::Scene::MESHRENDERERS) {
        renderer->update();
    }
}

void key_callback(GLFWwindow* window, int key,int scancode,int action,int mods) {
    if (key == GLFW_KEY_ESCAPE)
        glfwTerminate();
    if (action == GLFW_PRESS) {

    }
}

int main() {
    std::cout << "Main initializing" << std::endl;
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(720, 720, "PROGRAM", NULL, NULL);

    /*Always on top*/
    HWND hwnd = glfwGetWin32Window(window);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
             SWP_NOMOVE | SWP_NOSIZE);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window,key_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //GLAD initializing
    if(!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to load GLAD" << std::endl;
        return -1;
    }

    /*Start fucntion runs only once*/
    start();

    glfwSetWindowPos(window, 1920-720, 1200-720);

    /*This is a cli object that runs on another thread, represents app interface*/
    Commander commander0 = Commander();//New cmd

    /*This gl function sets v-sync*/
    glfwSwapInterval(1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        /* GL_DEPTH_BUFFER_BIT checks depth of the objects*/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*Update function runs frame by frame*/
        update();

        /*Commander break call*/
        if (!commander0.isRunning()) break;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;







    return 0;
}