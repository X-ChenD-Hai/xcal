file(GLOB_RECURSE SOURCES *.cc)

add_executable(test_animation ${SOURCES})

target_link_libraries(test_animation PRIVATE
    GTest::gtest GTest::gtest_main
    xcal
)

add_xcal_test(animation)
