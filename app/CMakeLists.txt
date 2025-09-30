add_executable(app)
target_sources(app PUBLIC main.cc)
target_link_libraries(app PRIVATE
    xcal
    xcal_glfw
    xcal_opengl
)
set_target_properties(app PROPERTIES
    OUTPUT_NAME "xcal"
)
