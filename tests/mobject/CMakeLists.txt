add_executable(test_mobject test_circle.cc)

target_link_libraries(test_mobject PRIVATE
    GTest::gtest GTest::gtest_main
    xcal
)

# 注册 mobject 测试
add_test(NAME test_mobject COMMAND test_mobject)
