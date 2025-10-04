#ifndef GIZMOS_HPP
#define GIZMOS_HPP

#include<glm/gtc/matrix_transform.hpp>
#include<glm/vec3.hpp>



namespace Objects { class Object;}
namespace Interface {
    class Gizmos {
    public:
        static const glm::mat4 GETMODEL();
        static Objects::Object* PARENT;
        static const glm::vec3 GETCOLOR();
    };

} // Interface

#endif //GIZMOS_HPP
