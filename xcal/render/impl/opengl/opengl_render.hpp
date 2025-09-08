#pragma once
#include <cstddef>
#include <memory>
#include <unordered_map>
#include <vector>
#include <xcal/render/core/render.hpp>
#include <xcal/render/impl/opengl/core/typedef.hpp>
#include <xcal/render/impl/opengl/object/object.hpp>

#include "xcal/camera/core/abs_camera.hpp"

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
namespace xcal::render::opengl {
struct UIState;
class XCAL_API OpenGLRender : public xcal::render::Render {
    friend void ::framebuffer_size_callback(GLFWwindow* window, int w, int h);
    friend class UIState;

   private:
    GLFWwindow* window_{nullptr};
    std::unique_ptr<UIState> ui_state_{nullptr};
    std::unordered_map<mobject::MObject*, object::object_ptr> objects_;
    std::unique_ptr<camera::AbsCamera> default_camera_{nullptr};
    const camera::AbsCamera* current_camera_{nullptr};

   protected:
    void framebuffer_size_callback(GLFWwindow* window, int w, int h);

   private:
    void setup_scene();
    void render_ui();
    void setup_gl();
    void setup_glfw();
    void setup_imgui();

   public:
    void show(size_t width = 800, size_t height = 600);
    void render_frame();
    virtual void set_scene(Scene* scene) override;
    std::vector<char> read_pixels_char() const;
    xcal::camera::AbsCamera* default_camera() const {
        return default_camera_.get();
    }
    const xcal::camera::AbsCamera* current_camera() const {
        return current_camera_;
    }

   public:
    OpenGLRender(const OpenGLRender&) = delete;
    OpenGLRender& operator=(const OpenGLRender&) = delete;
    OpenGLRender(Scene* scene);
    virtual ~OpenGLRender() override;
};
}  // namespace xcal::render::opengl