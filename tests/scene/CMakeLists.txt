add_executable(test_scene test_scene.cc)

target_link_libraries(test_scene PRIVATE
    GTest::gtest GTest::gtest_main
    xcal
)

# 注册 scene 测试
add_xcal_test(scene)
