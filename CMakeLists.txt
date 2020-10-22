cmake_minimum_required(VERSION 3.5)

project(IKEA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(IKEA/src)
file(GLOB_RECURSE SOURCES "IKEA/src/*.cpp" "IKEA/src/main.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
