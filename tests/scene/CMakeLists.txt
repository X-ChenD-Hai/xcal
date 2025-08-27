add_executable(test_scene scene.cc)

target_link_libraries(test_scene PRIVATE
    GTest::gtest GTest::gtest_main
    xcal
)
