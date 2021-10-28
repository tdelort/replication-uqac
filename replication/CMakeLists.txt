cmake_minimum_required(VERSION 3.19)

project(Replication VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_library(UReplication)

add_subdirectory(src)
target_include_directories(include)