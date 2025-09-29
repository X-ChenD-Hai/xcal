/**
 * @file context.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-09-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <xcal/public.h>

#include <xcal/camera/core/fpscontroler.hpp>
#include <xcal/mobject/core/abs_mobject.hpp>

namespace xcal::animation {
class Timeline;
class AbsAnimation;
}  // namespace xcal::animation
namespace xcal::camera {
class AbsCamera;
}
namespace xcal::render {
class Render;
}
namespace xcal::mobject {
class MObject;
}
namespace xcal::render::opengl {
class OpenGLRender;
}
namespace xcal::render {
class XCAL_API Context {
    friend class xcal::render::Render;
    friend class xcal::render::opengl::OpenGLRender;

   protected:
    struct XCAL_API ObjectHandle {
        using mobject_t = xcal::mobject::AbsMObject;
        mobject_t* obj;
        std::string name;
        std::string type;
        explicit ObjectHandle(mobject_t* obj);
    };
    struct XCAL_API CameraHandle {
        using camera_t = xcal::camera::AbsCamera;
        camera_t* camera;
        std::string name;
        explicit CameraHandle(camera_t* camera);
        CameraHandle(camera_t* camera, const std::string& name);
    };
    struct XCAL_API TimelineHandle {
        animation::Timeline* timeline;
        std::string name;
        explicit TimelineHandle(animation::Timeline* timeline)
            : timeline(timeline),
              name(std::string("timeline:") +
                   std::to_string((size_t)timeline)) {}
    };
    struct XCAL_API AnimationHandle {
        animation::AbsAnimation* animation;
        std::string name;
        explicit AnimationHandle(animation::AbsAnimation* animation)
            : animation(animation),
              name(std::string("animation:") +
                   std::to_string((size_t)animation)) {}
    };

   private:
    std::vector<ObjectHandle> object_handles_{};
    std::vector<CameraHandle> camera_handles_{};
    std::vector<AnimationHandle> animation_handles_{};
    std::vector<TimelineHandle> timeline_handles_{};
    camera::FpsCameraControler fps_camera_controler_{nullptr};
    CameraHandle default_camera_handles_{nullptr, "default"};
    Render* renderer_{nullptr};
    double last_fps_;
    std::chrono::high_resolution_clock::time_point last_time_point_;
    std::chrono::high_resolution_clock::time_point last_update_time_point_;

   private:
    void update_fps_();

   public:
    explicit Context(Render* renderer);
    virtual ~Context() = default;

   public:
    void flush();
    std::vector<ObjectHandle>& object_handles() { return object_handles_; }
    std::vector<CameraHandle>& camera_handles() { return camera_handles_; }
    std::vector<AnimationHandle>& animation_handles() {
        return animation_handles_;
    }
    std::vector<TimelineHandle>& timeline_handles() {
        return timeline_handles_;
    }
    camera::FpsCameraControler& fps_camera_controler() {
        return fps_camera_controler_;
    }
    CameraHandle& default_camera_handle() { return default_camera_handles_; }
    Render* renderer() const { return renderer_; }
    double fps() const { return last_fps_; }
    void render_frame();

   public:
    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void before_swap_buffers() = 0;
    virtual void render() = 0;

   public:
    Context(const Context&) = delete;
    Context(Context&&) = delete;
    Context& operator=(const Context&) = delete;
    Context& operator=(Context&&) = delete;
};
}  // namespace xcal::render