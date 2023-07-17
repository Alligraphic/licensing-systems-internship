cmake_minimum_required(VERSION 3.23)
project(HttpClient)

set(CMAKE_CXX_STANDARD 23)

add_library(HttpClient SHARED library.cpp)
