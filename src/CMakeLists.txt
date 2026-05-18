cmake_minimum_required(VERSION 4.1.0)

file(GLOB_RECURSE SOURCE_FILES ./*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor)

# GLFW files
set(GLFW_INCLUDE_DIR ${VENDOR_DIR}/GLFW/include)
set(GLFW_LIBS ${VENDOR_DIR}/GLFW/lib/)

# Glad files
set(GLAD_INCLUDE_DIR ${VENDOR_DIR}/glad/include)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/vendor
    ${CMAKE_SOURCE_DIR}/src
    ${GLFW_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
)

# Only MinGW is supported for now
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${GLFW_LIBS}/mingw-w64/libglfw3.a
)
