cmake_minimum_required(VERSION 3.19)
 
project(ReplicationTests VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tests tests.cpp "client.cpp" "serveur.cpp")

add_subdirectory(externals)
add_subdirectory(replication)
target_link_libraries(Tests UReplication USocket USerialisation)