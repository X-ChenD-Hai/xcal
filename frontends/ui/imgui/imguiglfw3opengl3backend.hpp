/**
 * @file imguiglfw3opengl3backend.hpp
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

#include <imguibackend.hpp>

struct GLFWwindow;
namespace xcal::render::ui {
class XCAL_IMGUI_API ImGuiGlfw3OpenGL3Backend : public ImGuiBackend {
   private:
    GLFWwindow *window_{nullptr};

   public:
    explicit ImGuiGlfw3OpenGL3Backend(GLFWwindow *window) : window_(window) {}
    void init() override;
    void deinit() override;
    void new_frame() override;
    void draw_data() override;

   public:
    ImGuiGlfw3OpenGL3Backend(const ImGuiGlfw3OpenGL3Backend &) = delete;
    ImGuiGlfw3OpenGL3Backend(ImGuiGlfw3OpenGL3Backend &&) = delete;
    ImGuiGlfw3OpenGL3Backend &operator=(const ImGuiGlfw3OpenGL3Backend &) =
        delete;
    ImGuiGlfw3OpenGL3Backend &operator=(ImGuiGlfw3OpenGL3Backend &&) = delete;
};
}  // namespace xcal::render::ui