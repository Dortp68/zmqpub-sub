cmake_minimum_required(VERSION 3.16)

project(zmqclient)
set(SOURCE_EXE client.cpp)
add_executable(main ${SOURCE_EXE})

#find cppzmq wrapper, installed by make of cppzmq
find_package(cppzmq)
target_link_libraries(main cppzmq)
