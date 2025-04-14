cmake_minimum_required(VERSION 3.8)

project(mapa-cucei)
set(CMAKE_CXX_STANDARD 17)

add_executable(mapa-cucei main.cpp node.cpp nodelist.cpp connection.cpp)

install(TARGETS mapa-cucei RUNTIME DESTINATION bin)
