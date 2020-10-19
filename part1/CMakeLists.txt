cmake_minimum_required(VERSION 3.0.0)
project(part1 VERSION 0.1.0)

set(MTM_FLAGS_DEBUG "-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDBUG")

set(CMAKE_CXX_FLAGS ${MTM_FLAGS_DEBUG})

add_executable(part1 main.cpp IntMatrix.cpp Auxiliaries.cpp)
