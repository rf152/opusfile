cmake_minimum_required(VERSION 3.12)

include(${CMAKE_CURRENT_LIST_DIR}/libs/opus/cmake/OpusFunctions.cmake)


set(PROJECT opus_file)

project(${PROJECT} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR 1)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

enable_testing()

add_subdirectory(libs/opus)
add_subdirectory(src)
add_subdirectory(tests)
