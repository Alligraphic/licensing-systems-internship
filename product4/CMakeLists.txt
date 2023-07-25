cmake_minimum_required(VERSION 3.23)
project(product4)

set(CMAKE_CXX_STANDARD 23)

add_executable(product4 main.cpp HttpClient.cpp HttpClient.h Response.cpp Response.h)
