file(GLOB_RECURSE SOURCES *.cc)
set(BUILD_DYNAMIC_LIBRARY OFF)
xcal_add_library(xcal_imgui XCAL_IMGUI)
target_sources(xcal_imgui PRIVATE ${SOURCES})
target_include_directories(xcal_imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(xcal_imgui PRIVATE
    PUBLIC xcal
    PUBLIC imgui::imgui
)
