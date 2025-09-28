#pragma once

#include <xcal/public.h>

#include <xcal/camera/core/fpscontroler.hpp>
#include <xcal/mobject/core/abs_mobject.hpp>
#include <xcal/render/core/renderbackend.hpp>
#include <xcal/render/core/uicontext.hpp>
#include <xcal/scene/scene.hpp>

namespace xcal::render {
class RenderBackend;
class UiContext;
template <typename ObjectPtr = mobject::AbsMObject_ptr>
class Render {
   protected:
    using Scene = xcal::scene::Scene;

   private:
    Scene* scene_;
    RenderBackend* backend_;
    UiContext* ui_context_;

   protected:
    void init() {
        backend_->set_scene(scene_);
        ui_context_->set_backend(backend_);
        ui_context_->set_scene(scene_);
    }

   public:
    Render(Scene* scene, RenderBackend* render_backend, UiContext* ui_context)
        : scene_(scene), backend_(render_backend), ui_context_(ui_context) {}

    virtual void render_frame() {
        if (!backend_) return;
        if (!ui_context_) {
            backend_->new_frame();
            backend_->render();
            backend_->end_frame();
            return;
        }
        ui_context_->update_fps_();
        ui_context_->before_new_frame();
        backend_->new_frame();
        ui_context_->after_new_frame();
        backend_->render();
        ui_context_->before_end_frame();
        backend_->end_frame();
        ui_context_->after_end_frame();
    }

    Scene* scene() const { return scene_; }
    RenderBackend* backend() const { return backend_; }
    UiContext* ui_context() const { return ui_context_; }
};
}  // namespace xcal::render