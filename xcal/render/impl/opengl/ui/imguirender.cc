#include <imgui.h>

#include <xcal/render/impl/opengl/ui/imguirender.hpp>
#define ROLE UIRender
#define LABEL ImGuiUiRender
#include <xcal/utils/logmacrohelper.inc>

void xcal::render::opengl::ui::ImGuiUiRender::init() {
    _I("initializing ImGuiUiRender" _SELF);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    backend_->init();
}
void xcal::render::opengl::ui::ImGuiUiRender::deinit() {
    _I("deinitializing ImGuiUiRender" _SELF);
    backend_->deinit();
    ImGui::DestroyContext();
}
void xcal::render::opengl::ui::ImGuiUiRender::render() {
    backend_->new_frame();
    ImGui::NewFrame();
    render_ui();
    ImGui::Render();
}
void xcal::render::opengl::ui::ImGuiUiRender::before_swap_buffers() {
    backend_->draw_data();
}
xcal::bool_t xcal::render::opengl::ui::ImGuiUiRender::want_capture_mouse()
    const {
    return ImGui::GetIO().WantCaptureMouse;
}
xcal::bool_t xcal::render::opengl::ui::ImGuiUiRender::want_capture_keyboard()
    const {
    return ImGui::GetIO().WantCaptureKeyboard;
}