#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <xcal/render/impl/ui/imguiglfw3opengl3backend.hpp>

void xcal::render::ui::ImGuiGlfw3OpenGL3Backend::init() {
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
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