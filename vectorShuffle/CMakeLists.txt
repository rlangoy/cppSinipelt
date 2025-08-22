cmake_minimum_required(VERSION 3.31)
project(vectorShuffle)

# Require C++17 or newer
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build your executable
add_executable(${PROJECT_NAME} src/vectorShuffle.cpp)


