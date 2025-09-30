#include <imgui.h>

#include <xcal/camera/perspectivecamera.hpp>
#include <xcal/mobject/core/mobject.hpp>
#include <xcal/render/impl/ui/listui.hpp>
#include <xcal/render/core/render.hpp>
#include <xcmath/utils/show.hpp>

#define ROLE OpenGL
#define LABEL ListUi
#include <xcal/utils/logmacrohelper.inc>
#define _CONST_MPTR(mobj) static_cast<const xcal::mobject::MObject*>(mobj)
#define _CONST_CPTR(mobj) static_cast<const xcal::camera::AbsCamera*>(mobj)
#define _CONST_PCPTR(mobj) \
    static_cast<const xcal::camera::PerspectiveCamera*>(mobj)
#define _PCPTR(mobj) static_cast<xcal::camera::PerspectiveCamera*>(mobj)

bool xcal::render::ui::ListUi::render_vec3f_edit(
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
void xcal::render::ui::ListUi::render_obj(ObjectHandle& obj) {
    // namespace I = ImGui;
    // if (I::CollapsingHeader(obj.name.c_str())) {
    //     I::Text("pos: ");
    //     tmp_ = _CONST_MPTR(obj.obj)->pos().x();
    //     switch (obj.obj->type()) {
    //         case xcal::mobject::Type::Circle:
    //             static_cast<mobject::Circle*>(obj.obj)->pos();
    //         default:
    //             break;
    //     }
    //     if (I::InputFloat("X", &tmp_)) {
    //         obj.obj->pos().x() = tmp_;
    //         _D("updating x of object: " << obj.obj << " to: " << tmp_
    //                                     << " change state: "
    //                                     << obj.obj->pos().is_changed());
    //     }
    //     tmp_ = _CONST_MPTR(obj.obj)->pos().y();
    //     if (I::InputFloat("Y", &tmp_)) obj.obj->pos().y() = tmp_;
    //     I::Text("depth: ");
    //     tmp_ = _CONST_MPTR(obj.obj)->depth();
    //     if (I::InputFloat("Depth", &tmp_)) obj.obj->depth() = tmp_;
    // }
}
void xcal::render::ui::ListUi::render_camera(CameraHandle& cam) {
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
            tmp_ = _CONST_PCPTR(cam.camera)->fov();
            if (I::InputFloat("FOV", &tmp_)) {
                _PCPTR(cam.camera)->fov() = tmp_;
                _D("updating fov of camera: "
                   << cam.camera << " to: " << tmp_ << " change state: "
                   << _PCPTR(cam.camera)->fov().is_changed());
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
void xcal::render::ui::ListUi::render_animation(AnimationHandle& anim) {
    if (!anim.animation) return;
    namespace I = ImGui;
    if (I::CollapsingHeader(anim.name.c_str())) {
        int id = 0;
    }
}
void xcal::render::ui::ListUi::render_timeline(
    TimelineHandle& timeline) {
    if (!timeline.timeline) return;
    namespace I = ImGui;
    if (I::CollapsingHeader(timeline.name.c_str())) {
    }
    if (I::Button("Play")) {
        _I("play timeline:" << timeline.timeline);
        renderer()->play_timeline(timeline.timeline);
    }
}
void xcal::render::ui::ListUi::render_ui() {
    namespace I = ImGui;
    if (!show_) return;
    default_camera_handle().camera = renderer()->default_camera();
    I::Begin("XCAL UI", &show_);
    I::SetWindowFontScale(2);
    int id = 0;
    if (I::CollapsingHeader("Objects")) {
        for (int i = 0; i < object_handles().size(); ++i) {
            I::PushID(++id);
            render_obj(object_handles()[i]);
            I::PopID();
        }
    }
    if (I::CollapsingHeader("Cameras")) {
        I::PushID(++id);
        render_camera(default_camera_handle());
        I::PopID();

        for (int i = 0; i < camera_handles().size(); ++i) {
            I::PushID(++id);
            render_camera(camera_handles()[i]);
            I::PopID();
        }
    }
    if (I::CollapsingHeader("Timelines")) {
        for (int i = 0; i < timeline_handles().size(); ++i) {
            I::PushID(++id);
            render_timeline(timeline_handles()[i]);
            I::PopID();
        }
    }
    if (I::CollapsingHeader("Animations")) {
        for (int i = 0; i < animation_handles().size(); ++i) {
            I::PushID(++id);
            render_animation(animation_handles()[i]);
            I::PopID();
        }
    }
    I::Text("fps: %.3f", 1.f / fps());
    I::End();
}
