#ifndef WRITER_HPP
#define WRITER_HPP
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>


struct Property;

struct Section {
    std::stringstream ss;
};

class Writer{
public:
    Writer();
    void writeClass(std::string className, std::string parent, std::vector<Property>* classProps);
    void writeGenerated(std::string generatedPath);



    Section* _include = new Section();
    Section* _function = new Section();
};



#endif //WRITER_HPP
