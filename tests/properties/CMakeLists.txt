add_executable(test_properties test_color.cc)

target_link_libraries(test_properties PRIVATE
    GTest::gtest GTest::gtest_main
    xcal
)
