cmake_minimum_required(VERSION 3.15)
project(xcal VERSION 0.1.0 LANGUAGES C CXX)
find_package(GTest REQUIRED)
find_package(xclogger REQUIRED)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DENVMAIN_VERSION="${PROJECT_VERSION}")

add_subdirectory(src)

