#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <imguiglfw3opengl3backend.hpp>
#include <print>

void xcal::render::ui::ImGuiGlfw3OpenGL3Backend::init() {
    std::println(std::cerr, "ImGuiGlfw3OpenGL3Backend::init {}",
                 (void*)window_);
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    std::println(std::cerr, "ImGui_ImplGlfw_InitForOpenGL");
    ImGui_ImplOpenGL3_Init("#version 330 core");
    std::println(std::cerr, "ImGui_ImplOpenGL3_Init");
}
void xcal::render::ui::ImGuiGlfw3OpenGL3Backend::deinit() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
};
void xcal::render::ui::ImGuiGlfw3OpenGL3Backend::new_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
}
void xcal::render::ui::ImGuiGlfw3OpenGL3Backend::draw_data() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};