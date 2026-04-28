#include <iostream>

#include "Generator.hpp"

#define PROJECT_PATH "D:\\Projects\\OpenGL\\Project1"
#define TEST_PATH "D:\\Projects\\OpenGL\\Introspector"


int main() {
    Generator(PROJECT_PATH);
    std::cout << "Introspector successfully ran!" << std::endl;
    return 0;
}