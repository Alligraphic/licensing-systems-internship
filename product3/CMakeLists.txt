cmake_minimum_required(VERSION 3.23)
project(product3)

find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(product3 main.cpp HttpClient.cpp HttpClient.h Response.cpp Response.h)

target_link_libraries(product3 OpenSSL::Crypto)