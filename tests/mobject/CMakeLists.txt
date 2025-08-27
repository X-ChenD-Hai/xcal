add_executable(test_mobject test_circle.cc)

target_link_libraries(test_mobject PRIVATE
    GTest::gtest GTest::gtest_main
    xcal
)
