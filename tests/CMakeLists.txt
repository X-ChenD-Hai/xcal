find_package(GTest REQUIRED)


add_executable(test_opengl opengl.cc)
target_link_libraries(test_opengl PRIVATE
    glad::glad
    glfw
)
add_subdirectory(scene)