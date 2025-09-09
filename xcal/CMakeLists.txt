if(BUILD_DYNAMIC_LIBRARY)
    add_library(xcal SHARED)
    target_compile_definitions(xcal
        PUBLIC XCAL_ENABLE_DYNAMIC_LIBRARY
        PRIVATE XCAL_BUILD
    )
else()
    add_library(xcal STATIC)
endif()
if(BUILD_VIDEOCODEC)
    add_library(ffmpegcodec SHARED ${CMAKE_CURRENT_SOURCE_DIR}/render/codec/ffmpegcodec.cc)
    target_compile_definitions(ffmpegcodec
        PRIVATE XCAL_CODEC_BUILD
        PUBLIC XCAL_CODEC_ENABLE_DYNAMIC_LIBRARY
    )
    target_include_directories(ffmpegcodec
        PRIVATE
        ${FFMPEG_INCLUDE_DIRS}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
    )
    target_link_directories(ffmpegcodec PRIVATE
        ${FFMPEG_LIBRARY_DIRS}
    )
    target_link_libraries(ffmpegcodec
        PRIVATE
        ${FFMPEG_LIBRARIES}
        PUBLIC
        xclogger::zmq_support
    )
    target_link_libraries(xcal PUBLIC ffmpegcodec)
endif()
file(GLOB_RECURSE SOURCES *.cc)
list(REMOVE_ITEM SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/render/codec/ffmpegcodec.cc
)

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
    imgui::imgui
)

add_executable(xcal_app)
target_sources(xcal_app PUBLIC main.cc)

target_link_libraries(xcal_app PRIVATE
    xcal
)
