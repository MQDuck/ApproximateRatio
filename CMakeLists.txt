cmake_minimum_required(VERSION 3.9)
project(ApproximateRatio)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lpthread")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(ApproximateRatio main.cpp ApproximateRatio.hpp)