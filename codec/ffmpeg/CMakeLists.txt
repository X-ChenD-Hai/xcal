find_package(FFMPEG REQUIRED)
file(GLOB_RECURSE SOURCES *.cc *.h)

xcal_add_library(ffmpeg_codec XCAL_FFMPEG)
target_sources(ffmpeg_codec PRIVATE ${SOURCES})
target_include_directories(ffmpeg_codec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ffmpeg_codec
    PRIVATE ${FFMPEG_INCLUDE_DIRS}
)
target_link_directories(ffmpeg_codec
    PRIVATE ${FFMPEG_LIBRARY_DIRS}
)
target_link_libraries(ffmpeg_codec
    PUBLIC xcal
    PRIVATE ${FFMPEG_LIBRARIES}
)
