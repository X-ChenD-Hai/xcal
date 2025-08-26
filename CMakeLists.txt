cmake_minimum_required(VERSION 3.15)
project(xcal VERSION 0.1.0 LANGUAGES C CXX)
find_package(xclogger REQUIRED)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(tests)

