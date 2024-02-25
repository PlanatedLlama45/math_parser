cmake_minimum_required(VERSION 3.5.0)
project(math_parser VERSION 1.0.0)

add_executable (
    math_parser
    
    src/main.cpp
    src/ast.hpp
    src/ast.cpp
    src/string_util.hpp
    src/string_util.cpp
)
