file(GLOB_RECURSE SOURCES *.cc)
add_executable(test_camera ${SOURCES})

target_link_libraries(test_camera PRIVATE
    GTest::gtest GTest::gtest_main
    xcal
)

# 注册 camera 测试
add_test(NAME test_camera COMMAND test_camera)
