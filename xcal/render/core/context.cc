#include <xcal/camera/core/abs_camera.hpp>
#include <xcal/mobject/core/mobject.hpp>
#include <xcal/render/core/context.hpp>
#include <xcal/render/core/render.hpp>

#define ROLE UIRender
#define LABEL Context
#include <xcal/utils/logmacrohelper.inc>

xcal::render::Context::ObjectHandle::ObjectHandle(mobject_t* obj)
    : obj(obj),
      name(std::string(xcal::to_string(obj->type())) + ": " +
           std::to_string((size_t)obj)),
      type(xcal::to_string(obj->type())) {
    _D("creating object handle for object: " << obj << " with name: " << name
                                             << " type: " << type);
}
xcal::render::Context::CameraHandle::CameraHandle(camera_t* camera)
    : camera(camera),
      name(std::string(xcal::to_string(camera->type())) + ": " +
           std::to_string((size_t)camera)) {
    _D("creating camera handle for camera: " << camera);
}

xcal::render::Context::CameraHandle::CameraHandle(camera_t* camera,
                                                  const std::string& name)
    : camera(camera),
      name(std::string(xcal::to_string(camera->type())) + ": " +
           std::to_string((size_t)camera)) {
    _D("creating camera handle for camera: " << camera);
}

void xcal::render::Context::update_fps_() {
    if (std::chrono::duration_cast<std::chrono::duration<float>>(
            std::chrono::high_resolution_clock::now() - last_update_time_point_)
            .count() > 0.5f) {
        last_fps_ =
            std::chrono::duration_cast<std::chrono::duration<float>>(
                std::chrono::high_resolution_clock::now() - last_time_point_)
                .count();
        last_update_time_point_ = std::chrono::high_resolution_clock::now();
    }
    last_time_point_ = std::chrono::high_resolution_clock::now();
}
void xcal::render::Context::render_() {
    update_fps_();
    render();
}
xcal::render::Context::Context(Render* renderer)
    : renderer_(renderer),
      default_camera_handles_(renderer->default_camera(), "default"),
      fps_camera_controler_(renderer->default_camera()) {}
void xcal::render::Context::flush() {
    _D("flushing UIRender" _SELF);
    object_handles_.clear();
    camera_handles_.clear();
    timeline_handles_.clear();
    animation_handles_.clear();
    if (renderer_ && renderer_->scene()) {
        for (auto& obj : renderer_->scene()->mobjects()) {
            object_handles_.emplace_back(obj.get());
        }
        for (auto& cam : renderer_->scene()->cameras()) {
            camera_handles_.emplace_back(cam.get());
        }
        for (auto& light : renderer_->scene()->timelines()) {
            timeline_handles_.emplace_back(light.get());
        }
        for (auto& anim : renderer_->scene()->animations()) {
            animation_handles_.emplace_back(anim.get());
        }
    }
}
