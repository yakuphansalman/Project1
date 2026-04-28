#ifndef OBJECT_LIGHT_HPP
#define OBJECT_LIGHT_HPP

#include "objects/Object.hpp"
#include "components/Light.hpp"
using namespace Components;
namespace Objects {
    class Light : public Object{
    public:
        Light();
        Light(const std::string name);
        Components::Light* getComponent();
    private:
        Components::Light* m_Light;
    };

} // Objects

#endif //LIGHT_HPP
