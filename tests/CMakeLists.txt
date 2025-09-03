find_package(GTest REQUIRED)
macro(add_xcal_test name)
    add_test(NAME ${name} COMMAND test_${name})
    set_tests_properties(${name} PROPERTIES
        ENVIRONMENT "PATH=$<TARGET_FILE_DIR:xcal>;$ENV{PATH}")
endmacro()

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
