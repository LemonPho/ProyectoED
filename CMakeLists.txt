cmake_minimum_required(VERSION 3.10)
project(mapa-cucei)

set(CMAKE_CXX_STANDARD 17)

# Include headers
include_directories(include)

# Collect source and header files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# Define the executable target
add_executable(mapa-cucei ${SOURCES} ${HEADERS})

# Optional: Copy data files to the build directory so they’re accessible at runtime
file(COPY data/ DESTINATION ${CMAKE_BINARY_DIR}/data)

# Optional: Install rule (for make install or packaging)
install(TARGETS mapa-cucei RUNTIME DESTINATION bin)
