#ifndef READER_HPP
#define READER_HPP
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

struct Property {
    std::string name, type, className;
};

class Reader{
public:
    Reader();
    int readAndMap(std::string className,std::string path);

    std::map<std::string, std::vector<Property>*>* getClassMap();
private:
    std::string _class;
    std::map<std::string,std::vector<Property>*> _classMap;
};



#endif //READER_HPP
