cmake_minimum_required(VERSION 3.23)
project(product7)

set(CMAKE_CXX_STANDARD 23)

add_executable(product7 main.cpp)

target_link_libraries(product7 -lOpenGL32 -lfreeGLUT)