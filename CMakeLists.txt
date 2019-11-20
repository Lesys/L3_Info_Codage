cmake_minimum_required(VERSION 3.10.2)
project(Codage)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(tp1_A ${SOURCES})

target_link_libraries(tp1_A m)
