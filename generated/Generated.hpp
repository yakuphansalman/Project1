#ifndef GENERATED_HPP
#define GENERATED_HPP
#include <iostream>
#include <map>
#include <vector>

#define REGISTER_PROPERTY(Name, Type, Class) \
{Prop{#Name, #Type, offsetof(Class, Name) } }

struct Prop {
    std::string name, type;
    size_t offset;
    Prop(std::string n, std::string t, size_t o)
        : name(std::move(n)), type(std::move(t)), offset(o) {}
};

class Generated {
public:
    void RegisterAllProperties();
    Generated() {
        std::cout << "***GENERATED***" << std::endl;
        for (auto p : _classMap["object"]) {
            std::cout << p.type  << "\t" << p.name << "\t" << p.offset <<std::endl;
        }
    }
    std::map<std::string,std::vector<Prop>> getClassMap() {return _classMap;}
private:
    std::map<std::string,std::vector<Prop>> _classMap;
    std::vector<Prop> props;
};

#endif