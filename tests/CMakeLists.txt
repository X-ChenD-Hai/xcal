find_package(GTest REQUIRED)

add_executable(test_opengl opengl.cc)
target_link_libraries(test_opengl PRIVATE
    ${OPENGL_BACKEND_LIBS}
    glfw
)
target_include_directories(test_opengl PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

add_subdirectory(scene)
add_subdirectory(properties)
add_subdirectory(mobject)
add_subdirectory(camera)
