file(GLOB_RECURSE SOURCES *.cc *.h)

add_executable(test_properties ${SOURCES})

target_link_libraries(test_properties PRIVATE
    GTest::gtest GTest::gtest_main
    xcal
)

# 注册 properties 测试
add_test(NAME test_properties COMMAND test_properties)
