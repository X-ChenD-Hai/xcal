#pragma once

#include <xcal/public.h>

#include <xcal/camera/core/fpscontroler.hpp>
#include <xcal/mobject/core/abs_mobject.hpp>

namespace xcal::render {

class Scene;
class RenderBackend {
   public:
    virtual void set_scene(Scene* scene) = 0;
    virtual void new_frame() {};
    virtual void render() {};
    virtual void end_frame() {};
    virtual ~RenderBackend() = default;
};
class UiContext {
    template <typename ObjectPtr = mobject::AbsMObject_ptr>
    friend class Reender;

   private:
    double last_fps_;
    std::chrono::high_resolution_clock::time_point last_time_point_;
    std::chrono::high_resolution_clock::time_point last_update_time_point_;

   private:
    void update_fps_() {
        if (std::chrono::duration_cast<std::chrono::duration<float>>(
                std::chrono::high_resolution_clock::now() -
                last_update_time_point_)
                .count() > 0.5f) {
            last_fps_ =
                std::chrono::duration_cast<std::chrono::duration<float>>(
                    std::chrono::high_resolution_clock::now() -
                    last_time_point_)
                    .count();
            last_update_time_point_ = std::chrono::high_resolution_clock::now();
        }
        last_time_point_ = std::chrono::high_resolution_clock::now();
    }

   public:
    double fps() { return last_fps_; }

   public:
    virtual void set_backend(RenderBackend* backend) = 0;
    virtual void set_scene(Scene* scene) = 0;
    virtual void before_new_frame() {};
    virtual void after_new_frame() {};
    virtual void before_end_frame() {};
    virtual void after_end_frame() {};
};
template <typename ObjectPtr = mobject::AbsMObject_ptr>
class Reender {
   private:
    Scene* scene;
    RenderBackend* render_backend;
    UiContext* ui_context;

   private:
   public:
    Reender(Scene* scene, RenderBackend* render_backend, UiContext* ui_context)
        : scene(scene), render_backend(render_backend), ui_context(ui_context) {
        render_backend->set_scene(scene);
        ui_context->set_backend(render_backend);
        ui_context->set_scene(scene);
    }

    virtual void render_frame() {
        ui_context->update_fps_();
        ui_context->before_new_frame();
        render_backend->new_frame();
        ui_context->after_new_frame();
        render_backend->render();
        ui_context->before_end_frame();
        render_backend->end_frame();
        ui_context->after_end_frame();
    }
};
}  // namespace xcal::render