cmake_minimum_required(VERSION 3.23)
project(Product1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Product1 main.cpp HttpClient.cpp HttpClient.h Response.cpp Response.h)
