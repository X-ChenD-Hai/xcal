#include <xcal/render/impl/opengl/opengl_render.hpp>
#include <xcal/render/impl/opengl/ui/uirender.hpp>

//
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#undef OUT  // undefine OUT macro to avoid conflict with xcal::OUT

#define ROLE OpenGL
#define LABEL UIRender
#include <xcal/utils/logmacrohelper.inc>
#define _CONST_MPTR(mobj) static_cast<const xcal::mobject::MObject*>(mobj)

xcal::render::opengl::ui::UIRender::ObjectHandle::ObjectHandle(mobject_t* obj)
    : obj(obj),
      name(std::string(xcal::to_string(obj->type())) + ": " +
           std::to_string((size_t)obj)),
      type(xcal::to_string(obj->type())),
      x(_CONST_MPTR(obj)->pos().x()),
      y(_CONST_MPTR(obj)->pos().y()),
      depth(_CONST_MPTR(obj)->depth()) {}
void xcal::render::opengl::ui::UIRender::flush() {
    object_handles.clear();
    if (renderer && renderer->scene()) {
        for (auto& obj : renderer->scene()->mobjects()) {
            object_handles.emplace_back(obj.get());
        }
    }
}
void xcal::render::opengl::ui::UIRender::render_obj(ObjectHandle& obj, int id) {
    namespace I = ImGui;
    I::PushID(id);
    if (I::CollapsingHeader(obj.name.c_str())) {
        I::Text("pos: ");
        tmp = _CONST_MPTR(obj.obj)->pos().x();
        if (I::InputFloat("X", &tmp)) {
            obj.obj->pos().x() = tmp;
            _D("updating x of object: " << obj.obj << " to: " << tmp
                                        << " change state: "
                                        << obj.obj->pos().is_changed());
        }
        tmp = _CONST_MPTR(obj.obj)->pos().y();
        if (I::InputFloat("Y", &tmp)) obj.obj->pos().y() = tmp;
        I::Text("depth: ");
        tmp = _CONST_MPTR(obj.obj)->depth();
        if (I::InputFloat("Depth", &tmp)) obj.obj->depth() = tmp;
    }
    I::PopID();
}
void xcal::render::opengl::ui::UIRender::render_ui() {
    namespace I = ImGui;
    if (!show) return;
    I::Begin("Hello, world!", &show);
    I::SetWindowFontScale(2);
    for (size_t i = 0; i < object_handles.size(); ++i) {
        render_obj(object_handles[i], (int)i);
    }
    I::End();
}
void xcal::render::opengl::ui::UIRender::init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(renderer->window_, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
};
void xcal::render::opengl::ui::UIRender::deinit() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
};
void xcal::render::opengl::ui::UIRender::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    render_ui();
    ImGui::Render();
};
void xcal::render::opengl::ui::UIRender::before_swap_buffers() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};