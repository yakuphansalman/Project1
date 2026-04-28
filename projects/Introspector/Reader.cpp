#include "Reader.hpp"

Reader::Reader() {
    std::cout << "READER INITIALIZED " << std::endl;
}



int Reader::readAndMap(std::string className, std::string path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "Could not open file : " << path << std::endl;
        return 0;
    }
    std::cout << "READING FILE : " << path << std::endl;


    _classMap[className] = new std::vector<Property>;
    std::string str;
    while (file >> str) {
        if (str.compare("PROPERTY(SAVE)") == 0) {
            Property prop;
            file >> prop.type;
            file >> prop.name;
            if (prop.name.ends_with(';'))
                prop.name = prop.name.substr(0,prop.name.size()-1);//Each definition has to end with a semicolon, so we discarded it
            _classMap[className]->push_back(prop);
        }
    }
    if (_classMap[className]->empty()) {
        free(_classMap[className]);
        return 0;
    }
    std::cout << "MAPPED CLASS : " << className << std::endl;
    file.close();
    return _classMap[className]->size();
}

std::map<std::string,std::vector<Property>*>* Reader::getClassMap() {
    return &_classMap;
}
