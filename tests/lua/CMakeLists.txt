# luajit 提供 pkg-config 模块:

#   # Just-in-time compiler for Lua
#   luajit
find_path(SOL2_INCLUDE_DIRS "sol/abort.hpp")
find_package(PkgConfig REQUIRED)
pkg_check_modules(LUAJIT REQUIRED luajit)
message(STATUS "Found LuaJIT: ${LUAJIT_INCLUDE_DIRS} ${LUAJIT_LIBRARIES} ${LUAJIT_LIBRARY_DIRS}")

add_executable(test_lua lua.cc)
target_link_libraries(test_lua PRIVATE
    ${LUAJIT_LIBRARIES}
)
target_include_directories(test_lua PRIVATE
    ${LUAJIT_INCLUDE_DIRS}
    ${SOL2_INCLUDE_DIRS}
)
target_link_directories(test_lua PRIVATE
    ${LUAJIT_LIBRARY_DIRS}
)
