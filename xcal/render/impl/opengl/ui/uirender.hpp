
#pragma once

#include <xcal/public.h>

#include <chrono>
#include <cstddef>
#include <string>
#include <xcal/animation/core/timeline.hpp>
#include <xcal/animation/core/timelinedriver.hpp>
#include <xcal/camera/core/abs_camera.hpp>
#include <xcal/mobject/core/mobject.hpp>

namespace xcal::render::opengl {
class OpenGLRender;
}
namespace xcal::render::opengl::ui {
class UIRender {
    struct ObjectHandle {
        using mobject_t = xcal::mobject::MObject;
        mobject_t* obj;
        std::string name;
        std::string type;
        ObjectHandle(mobject_t* obj);
    };
    struct CameraHandle {
        using camera_t = xcal::camera::AbsCamera;
        camera_t* camera;
        std::string name;
        CameraHandle(camera_t* camera);
        CameraHandle(camera_t* camera, const std::string& name);
    };
    struct TimelineHandle {
        animation::Timeline* timeline;
        std::string name;
        TimelineHandle(animation::Timeline* timeline)
            : timeline(timeline),
              name(std::string("timeline:") +
                   std::to_string((size_t)timeline)) {}
    };
    struct AnimationHandle {
        animation::AbsAnimation* animation;
        std::string name;
        AnimationHandle(animation::AbsAnimation* animation)
            : animation(animation),
              name(std::string("animation:") +
                   std::to_string((size_t)animation)) {}
    };

    bool show_ = true;
    std::vector<ObjectHandle> object_handles_{};
    std::vector<CameraHandle> camera_handles_{};
    std::vector<AnimationHandle> animation_handles_{};
    std::vector<TimelineHandle> timeline_handles_{};
    CameraHandle default_camera_handles_{nullptr, "default"};
    OpenGLRender* renderer_{nullptr};
    float_t tmp_;
    xcmath::vec3<float_t> vec3f_tmp_;
    double last_fps_;
    std::chrono::high_resolution_clock::time_point last_time_point_;
    std::chrono::high_resolution_clock::time_point last_update_time_point_;

   protected:
    void update_fps();
    void render_obj(ObjectHandle& obj);
    void render_camera(CameraHandle& cam);
    void render_animation(AnimationHandle& anim);
    void render_timeline(TimelineHandle& timeline);
    bool render_vec3f_edit(const xcmath::vec3<float_t>& vec3f,
                           const char* label, const char* x_label = "x",
                           const char* y_label = "y",
                           const char* z_label = "z");

   public:
    UIRender(OpenGLRender* renderer);
    void init();
    void deinit();
    void flush();
    void render();
    void render_ui();
    void before_swap_buffers();
};
}  // namespace xcal::render::opengl::ui