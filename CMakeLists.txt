cmake_minimum_required(VERSION 3.31)
project(Project1)

set(CMAKE_CXX_STANDARD 20)

set(dependencies_DIR "${CMAKE_SOURCE_DIR}/../Dependencies")
set(glfw3_DIR "${dependencies_DIR}/GLFW/lib/cmake/glfw3")
set(glm_DIR "${dependencies_DIR}/glm")
set(glad_DIR "${dependencies_DIR}/GLAD")
set(stb_DIR "${dependencies_DIR}/stb")

SET(PROJECT_SOURCES
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${glad_DIR}/gl.c
        objects/master.cpp
        objects/master.hpp
        objects/Master.cpp
        objects/Master.hpp
        objects/Object.cpp
        objects/Object.hpp
        components/Transform.cpp
        components/Transform.hpp
        components/MeshRenderer.cpp
        components/MeshRenderer.hpp
        programs/ShaderProgram.cpp
        programs/ShaderProgram.hpp
        components/Component.cpp
        components/Component.hpp
        components/Camera.cpp
        components/Camera.hpp
        components/Light.cpp
        components/Light.hpp
        managers/Scene.cpp
        managers/Scene.hpp
        objects/Entity.cpp
        objects/Entity.hpp
        objects/Custom.cpp
        objects/Custom.hpp
        managers/FileManager.cpp
        managers/FileManager.hpp
        objects/Camera.cpp
        objects/Camera.hpp
        objects/Light.cpp
        objects/Light.hpp
        interface/Commander.cpp
        interface/Commander.hpp
        managers/Time.cpp
        managers/Time.hpp
        interface/Gizmos.cpp
        interface/Gizmos.hpp
)


set(CMAKE_PREFIX_PATH ${glfw3_DIR})
set(CMAKE_MODULE_PATH ${glfw3_DIR})

find_package(glfw3 3.2 REQUIRED)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME}  PRIVATE
        ${dependencies_DIR}
        ${glfw3_DIR}/../../../include
        ${glad_DIR}/include
        ${glm_DIR}
        ${stb_DIR}

        ${CMAKE_SOURCE_DIR}

)
target_link_libraries(${PROJECT_NAME} glfw opengl32)
