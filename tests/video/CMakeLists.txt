if(BUILD_VIDEOCODEC)
    add_executable(test_codec avcode.cc)
    target_link_libraries(test_codec PRIVATE
        ffmpegcodec
    )
endif()
