cmake_minimum_required(VERSION 3.31)
project(compmanager)

# Require C++20 or newer
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build your executable
add_executable(${PROJECT_NAME} src/compmanager.cpp)


