file(GLOB_RECURSE SOURCES *.cc *.h)
xcal_add_library(opengl XCAL_OPENGL_RENDERER)
set(RENDER_BACKEND glad CACHE STRING "Choose the rendering backend: glbinding or glad")
set_property(CACHE RENDER_BACKEND PROPERTY STRINGS glbinding glad)
if(RENDER_BACKEND STREQUAL "glbinding")
    find_package(glbinding REQUIRED)
    set(OPENGL_BACKEND_LIBS glbinding::glbinding glbinding::glbinding-aux)
    target_compile_definitions( opengl PRIVATE GL_BACKEND_GLBINDING=1
        XCAL_OPENGL_SHADER_DIR="${OPENGL_SHADER_DIR}/"
    )
elseif(RENDER_BACKEND STREQUAL "glad")
    find_package(glad REQUIRED)
    set(OPENGL_BACKEND_LIBS glad::glad)
    target_compile_definitions( opengl PRIVATE GL_BACKEND_GLAD=1
        XCAL_OPENGL_SHADER_DIR="${OPENGL_SHADER_DIR}/"
    )
else()
    message(FATAL_ERROR "Invalid rendering backend: ${RENDER_BACKEND}")
endif()

target_sources(opengl PRIVATE ${SOURCES})
target_include_directories(opengl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(opengl PUBLIC
    xcal
    ${OPENGL_BACKEND_LIBS}
)
