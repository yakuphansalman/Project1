#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#define SOURCE "D:\\Projects\\OpenGL\\Project1"
#define GENERATED "D:\\Projects\\OpenGL\\Introspector\\generated\\Generated.cpp"
#define TARGET "D:\\Projects\\OpenGL\\Introspector\\generated"

#include <string>
#include <string.h>
#include <fstream>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>

#include "Writer.hpp"
#include "Reader.hpp"
#include <filesystem>




class Generator {
public:
    Generator(std::string projectPath);
private:
    std::vector<Property> _properties;
    void generate(Reader* r, Writer* w,std::string path);
    void readClass(std::string path);
    void writeProperty(Property& property, std::fstream& file);
    void writeClass(std::vector<Property>& p);

    std::string _currentClass;
    std::map<std::string,std::vector<Property>> _classMap;

};



#endif //GENERATOR_HPP
