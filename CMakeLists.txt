cmake_minimum_required(VERSION 3.16)
project(mycrt)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(Mycrt)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC Mycrt)