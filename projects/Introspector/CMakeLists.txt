cmake_minimum_required(VERSION 3.31)
project(Introspector)

set(CMAKE_CXX_STANDARD 20)

add_executable(Introspector main.cpp
        Generator.cpp
        Generator.hpp
        Reader.cpp
        Reader.hpp
        Writer.cpp
        Writer.hpp
)

target_include_directories( Introspector PUBLIC
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/generated
        ${CMAKE_SOURCE_DIR}/test
)