#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include <iostream>

#include "../Master.hpp"

namespace Objects {
    class Object;
}


namespace Components {
    class Component : public Master {
    public:
        virtual void bindObject(Objects::Object* object);
    protected:
        Objects::Object *m_Object;
    private:

    };
}





#endif //COMPONENT_HPP
