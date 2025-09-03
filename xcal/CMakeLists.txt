if(BUILD_DYNAMIC_LIBRARY)
    add_library(xcal SHARED)
    target_compile_definitions(xcal PRIVATE XCAL_ENABLE_DYNAMIC_LIBRARY XCAL_BUILD)
else()
    add_library(xcal STATIC)
endif()
file(GLOB_RECURSE SOURCES *.cc)
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cc)
target_sources(xcal PRIVATE ${SOURCES})
target_include_directories(xcal PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(xcal PUBLIC
    xclogger::zmq_support
    # glad::glad
    xcmath::xcmath
    ${OPENGL_BACKEND_LIBS}
    glfw
)

add_executable(xcal_app)
target_sources(xcal_app PUBLIC main.cc)

target_link_libraries(xcal_app PRIVATE
    xcal
)
