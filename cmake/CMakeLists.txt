cmake_minimum_required(VERSION 2.8)

project(Neon)

set(cppsourcefiles
        ../src/error.cpp
        ../src/file.cpp
        ../src/ioparser.cpp
        ../src/molecule.cpp
        ../src/neon.cpp
        ../src/options.cpp
        ../src/processor.cpp
        ../src/reaction.cpp
        ../src/transform.cpp)

add_executable(neon ${cppsourcefiles})
set(CMAKE_CXX_FLAGS "-std=c++11 -pedantic -Wall -Wextra -Wconversion")

include_directories(/usr/local/include/tinyxml2)
target_link_libraries(neon /usr/local/lib/libtinyxml2.so)

include_directories(/usr/local/include/openbabel-2.0)
target_link_libraries(neon /usr/local/lib/libopenbabel.so)

