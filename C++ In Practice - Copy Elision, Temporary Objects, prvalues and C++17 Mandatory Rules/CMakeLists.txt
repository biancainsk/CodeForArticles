cmake_minimum_required(VERSION 3.10)
project(proj VERSION 0.1 LANGUAGES CXX)

# Set C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(proj main.cpp)

# Disable RVO and all optimization
target_compile_options(proj PRIVATE
    -fno-elide-constructors
    -O0
    -Wall -Wextra
)

# Print compile commands to verify
set(CMAKE_VERBOSE_MAKEFILE ON)