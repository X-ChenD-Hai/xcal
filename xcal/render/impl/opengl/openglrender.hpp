#pragma once
#include <xcal/public.h>

#include <memory>
#include <unordered_map>
#include <xcal/animation/core/timeline.hpp>
#include <xcal/animation/core/timelinedriver.hpp>
#include <xcal/camera/core/abs_camera.hpp>
#include <xcal/mobject/core/abs_mobject.hpp>
#include <xcal/render/core/render.hpp>
#include <xcal/render/impl/opengl/core/rendercommand.hpp>
#include <xcal/render/impl/opengl/core/typedef.hpp>
#include <xcal/render/impl/opengl/object/object.hpp>

namespace xcal::render {
class RenderBridge {};
class XCAL_API GlfwOpenglBridge{};

class XCAL_API OpenGLRender : public xcal::render::Render {
   private:
    std::unordered_map<mobject::AbsMObject *, opengl::object::object_ptr>
        objects_;
    std::unique_ptr<animation::TimelineDriver> playing_timeline_{nullptr};
    std::chrono::high_resolution_clock::time_point last_time_point_;
    std::unique_ptr<camera::AbsCamera> default_camera_{nullptr};
    const camera::AbsCamera *current_camera_{nullptr};

   protected:
    void setup_scene();

   public:
    void init(GetProcAddress get_proc_address) override;
    void before_render(int width, int height) override;
    void after_render() override;
    void render_frame() override;
    void set_scene(Scene *scene) override;
    bool_t play_timeline(animation::Timeline *timeline) override;
    void frame_resize(int width, int height) override;
    xcal::camera::AbsCamera *default_camera() const override {
        return default_camera_.get();
    }
    const xcal::camera::AbsCamera *current_camera() const override {
        return current_camera_;
    }

   public:
    explicit OpenGLRender(Scene *scene);
    ~OpenGLRender() override;

   public:
    OpenGLRender(const OpenGLRender &) = delete;
    OpenGLRender(OpenGLRender &&) = delete;
    OpenGLRender &operator=(const OpenGLRender &) = delete;
    OpenGLRender &operator=(OpenGLRender &&) = delete;
};
}  // namespace xcal::render