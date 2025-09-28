#pragma once
#include <xcal/scene/core/scene.hpp>

namespace xcal::render {
class RenderBackend;
class UiContext {
    template <typename ObjectPtr>
    friend class Render;

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
    virtual void set_scene(scene::Scene* scene) = 0;
    virtual void before_new_frame() {};
    virtual void after_new_frame() {};
    virtual void before_end_frame() {};
    virtual void after_end_frame() {};
};

}  // namespace xcal::render