
xcal_add_library(xcal XCAL)
file(GLOB_RECURSE SOURCES *.cc)
list(REMOVE_ITEM SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cc
)

target_sources(xcal PRIVATE ${SOURCES})
target_include_directories(xcal PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(xcal
    PUBLIC
    xclogger::zmq_support
    xcmath::xcmath
    PRIVATE
    ${OPENGL_BACKEND_LIBS}
    glfw
    imgui::imgui
)

add_executable(xcal_app)
target_sources(xcal_app PUBLIC main.cc)

target_link_libraries(xcal_app PRIVATE
    xcal
)
