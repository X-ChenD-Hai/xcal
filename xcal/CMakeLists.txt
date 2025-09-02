add_library(xcal STATIC)
file(GLOB_RECURSE SOURCES *.cc)
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cc)
target_sources(xcal PRIVATE ${SOURCES})
target_link_libraries(xcal PUBLIC
    xclogger::zmq_support
    # glad::glad
    xcmath::xcmath
    glbinding::glbinding glbinding::glbinding-aux
    glfw
)

add_executable(xcal_app)
target_sources(xcal_app PUBLIC main.cc)

target_link_libraries(xcal_app PRIVATE
    xcal
)
