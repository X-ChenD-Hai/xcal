#include <cstddef>
#include <xcal/camera/perspectivecamera.hpp>
#include <xcal/render/impl/opengl/opengl_render.hpp>
#include <xcal/render/impl/opengl/ui/uirender.hpp>
#include <xcmath/utils/show.hpp>
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
#define _CONST_CPTR(mobj) static_cast<const xcal::camera::AbsCamera*>(mobj)
#define _CONST_PCPTR(mobj) \
    static_cast<const xcal::camera::PerspectiveCamera*>(mobj)
#define _PCPTR(mobj) static_cast<xcal::camera::PerspectiveCamera*>(mobj)

xcal::render::opengl::ui::UIRender::ObjectHandle::ObjectHandle(mobject_t* obj)
    : obj(obj),
      name(std::string(xcal::to_string(obj->type())) + ": " +
           std::to_string((size_t)obj)),
      type(xcal::to_string(obj->type())) {
    _D("creating object handle for object: " << obj << " with name: " << name
                                             << " type: " << type);
}
void xcal::render::opengl::ui::UIRender::flush() {
    _D("flushing UIRender" _SELF);
    object_handles_.clear();
    if (renderer_ && renderer_->scene()) {
        for (auto& obj : renderer_->scene()->mobjects()) {
            object_handles_.emplace_back(obj.get());
        }
        for (auto& cam : renderer_->scene()->cameras()) {
            camera_handles_.emplace_back(cam.get());
        }
    }
}
void xcal::render::opengl::ui::UIRender::render_obj(ObjectHandle& obj) {
    namespace I = ImGui;
    if (I::CollapsingHeader(obj.name.c_str())) {
        I::Text("pos: ");
        tmp_ = _CONST_MPTR(obj.obj)->pos().x();
        if (I::InputFloat("X", &tmp_)) {
            obj.obj->pos().x() = tmp_;
            _D("updating x of object: " << obj.obj << " to: " << tmp_
                                        << " change state: "
                                        << obj.obj->pos().is_changed());
        }
        tmp_ = _CONST_MPTR(obj.obj)->pos().y();
        if (I::InputFloat("Y", &tmp_)) obj.obj->pos().y() = tmp_;
        I::Text("depth: ");
        tmp_ = _CONST_MPTR(obj.obj)->depth();
        if (I::InputFloat("Depth", &tmp_)) obj.obj->depth() = tmp_;
    }
}
void xcal::render::opengl::ui::UIRender::render_ui() {
    namespace I = ImGui;
    if (!show_) return;
    default_camera_handles_.camera = renderer_->default_camera();
    I::Begin("XCAL UI", &show_);
    I::SetWindowFontScale(2);
    int id = 0;
    if (I::CollapsingHeader("Objects"))
        for (int i = 0; i < object_handles_.size(); ++i) {
            I::PushID(++id);
            render_obj(object_handles_[i]);
            I::PopID();
        }

    if (I::CollapsingHeader("Cameras")) {
        I::PushID(++id);
        render_camera(default_camera_handles_);
        I::PopID();

        for (int i = 0; i < camera_handles_.size(); ++i) {
            I::PushID(++id);
            render_camera(camera_handles_[i]);
            I::PopID();
        }
    }

    I::End();
}
void xcal::render::opengl::ui::UIRender::init() {
    _I("initializing UIRender" _SELF);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(renderer_->window_, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
};
void xcal::render::opengl::ui::UIRender::deinit() {
    _I("deinitializing UIRender" _SELF);
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
xcal::render::opengl::ui::UIRender::UIRender(OpenGLRender* renderer)
    : renderer_(renderer) {
    _I("constructing UIRender" _SELF);
}
xcal::render::opengl::ui::UIRender::CameraHandle::CameraHandle(camera_t* camera)
    : camera(camera),
      name(std::string(xcal::to_string(camera->type())) + ": " +
           std::to_string((size_t)camera)) {
    _D("creating camera handle for camera: " << camera);
};
void xcal::render::opengl::ui::UIRender::render_camera(CameraHandle& cam) {
    if (!cam.camera) return;

    namespace I = ImGui;
    if (I::CollapsingHeader(cam.name.c_str())) {
        int id = 0;
        {
            I::PushID(++id);
            if (render_vec3f_edit(_CONST_CPTR(cam.camera)->position().value(),
                                  "pos")) {
                cam.camera->position() = vec3f_tmp_;
                _D("updating position of camera: "
                   << cam.camera << " to: " << vec3f_tmp_
                   << " change state: " << cam.camera->position().is_changed());
            }
            I::PopID();
        }
        {
            I::PushID(++id);
            if (render_vec3f_edit(_CONST_CPTR(cam.camera)->target().value(),
                                  "target", "X", "Y", "Z")) {
                cam.camera->target() = vec3f_tmp_;
                _D("updating target of camera: "
                   << cam.camera << " to: " << vec3f_tmp_
                   << " change state: " << cam.camera->target().is_changed());
            }
            I::PopID();
        }
        {
            I::PushID(++id);
            if (render_vec3f_edit(_CONST_CPTR(cam.camera)->up().value(), "up",
                                  "X", "Y", "Z")) {
                cam.camera->up() = vec3f_tmp_;
                _D("updating up of camera: "
                   << cam.camera << " to: " << vec3f_tmp_
                   << " change state: " << cam.camera->up().is_changed());
            }
            I::PopID();
        }
        if (cam.camera->type() == xcal::camera::CameraType::Perspective) {
            I::Text("Perspective properties: ");
            I::Text("fov: ");
            tmp_ = _CONST_PCPTR(cam.camera)->far();
            if (I::InputFloat("FOV", &tmp_)) {
                _PCPTR(cam.camera)->far() = tmp_;
                _D("updating fov of camera: "
                   << cam.camera << " to: " << tmp_ << " change state: "
                   << _PCPTR(cam.camera)->far().is_changed());
            }
            I::Text("near: ");
            tmp_ = _CONST_PCPTR(cam.camera)->near();
            if (I::InputFloat("Near", &tmp_)) {
                _PCPTR(cam.camera)->near() = tmp_;
                _D("updating near of camera: "
                   << cam.camera << " to: " << tmp_ << " change state: "
                   << _PCPTR(cam.camera)->near().is_changed());
            }
            I::Text("far: ");
            tmp_ = _CONST_PCPTR(cam.camera)->far();
            if (I::InputFloat("Far", &tmp_)) {
                _PCPTR(cam.camera)->far() = tmp_;
                _D("updating far of camera: "
                   << cam.camera << " to: " << tmp_ << " change state: "
                   << _PCPTR(cam.camera)->far().is_changed());
            }
        }
    }
}
xcal::render::opengl::ui::UIRender::CameraHandle::CameraHandle(
    camera_t* camera, const std::string& name)
    : camera(camera), name(name) {
    _D("creating camera handle for camera: " << camera
                                             << " with name: " << name);
};
bool xcal::render::opengl::ui::UIRender::render_vec3f_edit(
    const xcmath::vec3<float_t>& vec3f, const char* label, const char* x_label,
    const char* y_label, const char* z_label) {
    namespace I = ImGui;
    auto tmp = vec3f;
    I::Text("%s: ", label);
    I::Text("%s: ", x_label);
    I::SameLine();
    I::InputFloat("##X", &tmp.x());
    I::Text("%s: ", y_label);
    I::SameLine();
    I::InputFloat("##Y", &tmp.y());
    I::Text("%s: ", z_label);
    I::SameLine();
    I::InputFloat("##Z", &tmp.z());
    if ((tmp == vec3f).all()) {
        return false;
    }
    vec3f_tmp_ = tmp;
    return true;
}
