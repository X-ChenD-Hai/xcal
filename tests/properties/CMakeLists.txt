file(GLOB_RECURSE SOURCES *.cc *.h)

add_executable(test_properties ${SOURCES})

target_link_libraries(test_properties PRIVATE
    GTest::gtest GTest::gtest_main
    xcal
)
