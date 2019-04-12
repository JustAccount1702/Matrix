cmake_minimum_required(VERSION 3.13)
project(Matrix)

set(CMAKE_CXX_STANDARD 14)

add_executable(main matrix.hpp main.cpp Fraction.hpp Fraction.cpp)

add_executable(test matrix.hpp test.cpp)
