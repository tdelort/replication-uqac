cmake_minimum_required(VERSION 3.19)

project(Replication VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_library(UReplication STATIC)
target_link_libraries(UReplication USerialisation USocket)

add_subdirectory(src)
target_include_directories(UReplication PUBLIC include)