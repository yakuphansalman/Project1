#ifndef GIZMOS_HPP
#define GIZMOS_HPP

#include<glm/gtc/matrix_transform.hpp>
#include<glm/vec3.hpp>
#include<glm/gtc/constants.hpp>



namespace Objects { class Object;}
namespace Interface {
    class Gizmos {
    public:
        static const glm::mat4 GETMODEL();
        static Objects::Object* PARENT;
        static const glm::vec3 GETCOLOR();
        static bool ISGLOBAL;
    };

} // Interface

#endif //GIZMOS_HPP
