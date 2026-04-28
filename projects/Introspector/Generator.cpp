#include "Generator.hpp"

#include <algorithm>

#include "Reader.hpp"
#include "Writer.hpp"


namespace fs = std::filesystem;

Generator::Generator(std::string projectPath) {
    std::cout << "GENERATOR RUNNING "<< std::endl;

    std::string generated = projectPath + "\\generated\\Generated.cpp";

    Reader* r = new Reader();
    Writer* w = new Writer();

    std::vector<fs::directory_entry> file_list;
    try {
        if (!fs::exists(projectPath) || !fs::is_directory(projectPath)) {
            std::cout << "Could not find the folder : "<< projectPath << std::endl;
            return;
        }
        for (const auto& input : fs::recursive_directory_iterator(projectPath)) {
            file_list.push_back(input);
        }
        std::reverse(file_list.begin(), file_list.end());

        int success = 0;

        for (const auto& input : file_list) {
            if (fs::is_regular_file(input)) {
                std::string className = input.path().filename().string();
                className = className.substr(0,className.length() - 4);
                if (!className.compare("Generated")) continue;//Ignore Generated files that created by itself

                std::string fileName = input.path().string();
                std::string ext = input.path().extension().string();

                std::string parent = input.path().parent_path().filename().string();

                if (!ext.compare(".hpp")) {
                    if (!(success = r->readAndMap(className,fileName)))
                        continue;
                }
                auto it = r->getClassMap()->find(className);
                if (!ext.compare(".cpp") && it != r->getClassMap()->end() && success) {
                    std::cout << "SUCCESS : " << success << std::endl;
                    w->writeClass(className,parent,(*r->getClassMap())[className]);
                }
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Error : " << e.what() << std::endl;
    }
    w->writeGenerated(generated);

}

