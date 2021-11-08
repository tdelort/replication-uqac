cmake_minimum_required(VERSION 3.19)
 
project(ReplicationTests VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(Main main.cpp Client.cpp Serveur.cpp Player.cpp Enemy.cpp)
add_subdirectory(externals)
add_subdirectory(replication)
target_link_libraries(Main UReplication USocket USerialisation)