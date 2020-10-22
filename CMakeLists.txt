cmake_minimum_required(VERSION 3.5)

project(IKEA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  message("Debug")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  message("Release")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DIKEA_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DIKEA_RELEASE")

include_directories(src)
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h" "src/main.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
