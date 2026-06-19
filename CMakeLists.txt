cmake_minimum_required(VERSION 4.1.0)
project(Renderer-Project)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor)

set(CMAKE_CXX_STANDARD_PREFIX ${PROJECT_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(${VENDOR_DIR}/assimp)
