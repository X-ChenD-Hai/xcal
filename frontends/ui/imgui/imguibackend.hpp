/**
 * @file imguibackend.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-09-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include XCAL_IMGUI_CONFIG_HEADER

namespace xcal::render::ui {
class XCAL_IMGUI_API ImGuiBackend {
    friend class ImGuiUiRender;
    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void new_frame() = 0;
    virtual void draw_data() = 0;

   public:
    ImGuiBackend() = default;
    virtual ~ImGuiBackend() = default;

   public:
    ImGuiBackend(const ImGuiBackend &) = delete;
    ImGuiBackend(ImGuiBackend &&) = delete;
    ImGuiBackend &operator=(const ImGuiBackend &) = delete;
    ImGuiBackend &operator=(ImGuiBackend &&) = delete;
};
}  // namespace xcal::render::ui