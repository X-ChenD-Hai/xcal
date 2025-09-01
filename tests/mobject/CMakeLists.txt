file(GLOB_RECURSE SOURCES *.cc)
add_executable(test_mobject ${SOURCES})

target_link_libraries(test_mobject PRIVATE
    GTest::gtest GTest::gtest_main
    xcal
)

# 注册 mobject 测试
add_test(NAME test_mobject COMMAND test_mobject)
