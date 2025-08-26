add_executable(xcal)
target_sources(xcal PUBLIC main.cc)

target_link_libraries(xcal PRIVATE
    xclogger::zmq_support
)
