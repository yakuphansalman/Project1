#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include <iostream>

#include "objects/Master.hpp"

namespace Objects {
    class Object;
}


namespace Components {
    class Component : public Objects::Master {
    public:
        virtual void bindObject(Objects::Object* object);
    protected:
        Objects::Object *m_Object;
    private:

    };
}





#endif //COMPONENT_HPP
