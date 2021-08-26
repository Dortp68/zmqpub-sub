cmake_minimum_required(VERSION 3.16)

project(zmqserver)
set(SOURCE_EXE server.cpp)
add_executable(main ${SOURCE_EXE})

#find cppzmq wrapper, installed by make of cppzmq
find_package(cppzmq)
target_link_libraries(main cppzmq)
