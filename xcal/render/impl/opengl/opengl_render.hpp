#pragma once
#include <xcal/public.h>

#include <memory>
#include <unordered_map>
#include <vector>
#include <xcal/animation/core/timeline.hpp>
#include <xcal/animation/core/timelinedriver.hpp>
#include <xcal/camera/core/abs_camera.hpp>
#include <xcal/mobject/core/abs_mobject.hpp>
#include <xcal/render/core/render.hpp>
#include <xcal/render/impl/opengl/core/rendercommand.hpp>
#include <xcal/render/impl/opengl/core/typedef.hpp>
#include <xcal/render/impl/opengl/object/object.hpp>

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
namespace xcal::render::opengl::ui {
class Context;
class UIRender;
}  // namespace xcal::render::opengl::ui
namespace xcal::render::opengl {
class XCAL_API OpenGLRender : public xcal::render::Render {
    friend void ::framebuffer_size_callback(GLFWwindow* window, int w, int h);
    friend class ui::UIRender;

   private:
    GLFWwindow* window_{nullptr};
    std::unique_ptr<Context> ui_render_{nullptr};
    std::unordered_map<mobject::AbsMObject*, object::object_ptr> objects_;
    std::unique_ptr<camera::AbsCamera> default_camera_{nullptr};
    std::unique_ptr<animation::TimelineDriver> playing_timeline_{nullptr};
    std::chrono::high_resolution_clock::time_point last_time_point_;
    const camera::AbsCamera* current_camera_{nullptr};
    std::vector<xcal::render::opengl::GL::RenderCommand> render_commands_;

   protected:
    void framebuffer_size_callback(GLFWwindow* window, int w, int h);

   private:
    void setup_scene();
    void setup_gl();
    void setup_glfw();

   public:
    bool_t play_timeline(animation::Timeline* timeline) override;
    void show(int width = 800, int height = 600);
    void render_frame() override;
    void set_scene(Scene* scene) override;
    std::vector<char> read_pixels_char() const;
    xcal::camera::AbsCamera* default_camera() const override {
        return default_camera_.get();
    }
    const xcal::camera::AbsCamera* current_camera() const override {
        return current_camera_;
    }

   public:
    explicit OpenGLRender(Scene* scene);
    ~OpenGLRender() override;

   public:
    OpenGLRender(OpenGLRender&&) = delete;
    OpenGLRender& operator=(OpenGLRender&&) = delete;
    OpenGLRender(const OpenGLRender&) = delete;
    OpenGLRender& operator=(const OpenGLRender&) = delete;
};
}  // namespace xcal::render::opengl