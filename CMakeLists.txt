cmake_minimum_required(VERSION 3.31)
project(Project1)

set(CMAKE_CXX_STANDARD 20)

set(dependencies_DIR "${CMAKE_SOURCE_DIR}/../Dependencies")
set(glm_DIR "${dependencies_DIR}/glm")
set(glad_DIR "${dependencies_DIR}/GLAD")
set(stb_DIR "${dependencies_DIR}/stb")
set(Assimp_DIR "${dependencies_DIR}/assimp")
set(AI_DIR "${dependencies_DIR}/ai")
set(INTROSPECTOR_EXE "D:/Projects/OpenGL/Introspector/cmake-build-debug/Introspector.exe")



set(GENERATED_FILE "${CMAKE_SOURCE_DIR}/generated/Generated.cpp")

add_subdirectory(projects/Introspector)

set(MAIN_PROJECT_SOURCES
    src/main.cpp)

add_custom_command(
        OUTPUT ${GENERATED_FILE}
        COMMAND Introspector "${CMAKE_SOURCE_DIR}/src" "${GENERATED_FILE}"
        DEPENDS Introspector
        COMMENT "Introspector calisiyor ve Generated.cpp olusturuluyor..."
        VERBATIM
)


SET(PROJECT_SOURCES
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${glad_DIR}/gl.c
        Master.cpp
        Master.hpp
        Master.cpp
        Master.hpp
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
        managers/TextureManager.cpp
        managers/TextureManager.hpp
        components/Material.cpp
        components/Material.hpp
        generated/Generated.cpp
        generated/Generated.hpp
        AI/TTS/ITTSEngine.cpp
        AI/TTS/ITTSEngine.hpp
        AI/TTS/PiperEngine.cpp
        AI/TTS/PiperEngine.hpp
)


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME}  PRIVATE
        ${dependencies_DIR}
        ${dependencies_DIR}/GLFW/include
        ${glad_DIR}/include
        ${glm_DIR}
        ${stb_DIR}
        ${AI_DIR}

        ${CMAKE_SOURCE_DIR}/AI


        ${CMAKE_SOURCE_DIR}

)
target_link_libraries(${PROJECT_NAME} "${dependencies_DIR}/GLFW/lib/glfw3.lib" opengl32)