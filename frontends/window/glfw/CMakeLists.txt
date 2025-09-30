file(GLOB_RECURSE SOURCES *.cc)
xcal_add_library(xcal_glfw XCAL_GLFW)
target_sources(xcal_glfw PRIVATE ${SOURCES})
target_include_directories(xcal_glfw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(xcal_glfw
    PUBLIC xcal
    PRIVATE glfw
    PRIVATE xcal_imgui
    PRIVATE xcal_opengl
)
