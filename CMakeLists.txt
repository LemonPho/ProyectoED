cmake_minimum_required(VERSION 3.10)

project(mapa-cucei)
set(CMAKE_CXX_STANDARD 17)

add_executable(mapa-cucei main.cpp node.cpp graph.cpp connection.cpp core.cpp nodemenu.cpp)

install(TARGETS mapa-cucei RUNTIME DESTINATION bin)
