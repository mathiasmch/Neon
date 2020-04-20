cmake_minimum_required(VERSION 2.8)

project(NeonTest)

set(CMAKE_CXX_FLAGS "-std=c++11 -D TESTS")

include_directories(/usr/local/include/tinyxml2)
include_directories(/usr/local/include/openbabel-2.0)
include_directories(/usr/local/include/gtest)

set(tests
        test_file
        test_ioparser
        test_molecule
        test_options
        test_processor
        test_reaction
        test_transform)

add_executable(test_file
                ../test_file.cpp
                ../utility.cpp
                ./../../src/error.cpp
                ./../../src/file.cpp
                ./../../src/molecule.cpp)

add_executable(test_ioparser
                ../test_ioparser.cpp
                ./../../src/error.cpp
                ./../../src/file.cpp
                ./../../src/ioparser.cpp
                ./../../src/molecule.cpp
                ./../../src/reaction.cpp)

add_executable(test_molecule
                ../utility.cpp
                ../test_molecule.cpp
                ./../../src/error.cpp
                ./../../src/molecule.cpp)

add_executable(test_options
                ../test_options.cpp
                ./../../src/error.cpp
                ./../../src/options.cpp
                ./../../src/reaction.cpp)

add_executable(test_processor
                ../utility.cpp
                ../test_processor.cpp
                ./../../src/error.cpp
                ./../../src/file.cpp
                ./../../src/ioparser.cpp
                ./../../src/molecule.cpp
                ./../../src/options.cpp
                ./../../src/processor.cpp
                ./../../src/reaction.cpp)

add_executable(test_reaction
                ../test_reaction.cpp
                ./../../src/error.cpp
                ./../../src/reaction.cpp)

add_executable(test_transform
                ../test_transform.cpp
                ./../../src/transform.cpp)

foreach(test ${tests})
    target_link_libraries(${test} /usr/local/lib/libtinyxml2.so)
    target_link_libraries(${test} /usr/local/lib/libopenbabel.so)
    target_link_libraries(${test} /usr/local/lib/libgtest.so /usr/local/lib/libgtest_main.so pthread)
endforeach()

