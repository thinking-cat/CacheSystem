cmake_minimum_required(VERSION 3.30)
project(CacheSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(CacheSystem main.cpp)

target_include_directories(CacheSystem include)