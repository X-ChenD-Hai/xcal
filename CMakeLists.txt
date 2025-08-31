cmake_minimum_required(VERSION 3.15)
project(xcal VERSION 0.1.0 LANGUAGES C CXX)
find_package(xclogger REQUIRED)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用 CTest 支持
include(CTest)
enable_testing()

# find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glbinding CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BUILD_TESTING OFF)
add_subdirectory(third_party/xcmath)
unset(BUILD_TESTING)
add_subdirectory(src)
add_subdirectory(tests)

# 代码格式化目标
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    if(WIN32)
        set(COMMAND_FORMAT PowerShell -File ${CMAKE_CURRENT_SOURCE_DIR}/tools/format-code.ps1 ${CLANG_FORMAT} ${CMAKE_SOURCE_DIR})
    else()
        set(COMMAND_FORMAT ${CMAKE_CURRENT_SOURCE_DIR}/tools/format-code.sh ${CLANG_FORMAT} ${CMAKE_SOURCE_DIR})
    endif()
    add_custom_target(format-code
        COMMAND ${COMMAND_FORMAT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Formatting source code with clang-format"
    )
    message(STATUS "clang-format found: ${CLANG_FORMAT}")
else()
    message(WARNING "clang-format not found, format-code target will not be available")
endif()
