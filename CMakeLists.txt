cmake_minimum_required(VERSION 3.10)
project(StringSearcher LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(search
    src/main.cpp
    src/naive_search.cpp
)

target_include_directories(search PRIVATE include)
