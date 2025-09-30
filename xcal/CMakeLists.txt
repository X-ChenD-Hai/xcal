
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
)

