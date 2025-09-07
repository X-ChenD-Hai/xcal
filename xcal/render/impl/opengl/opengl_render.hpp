#pragma once
#include <cstddef>
#include <unordered_map>
#include <vector>
#include <xcal/render/core/render.hpp>
#include <xcal/render/impl/opengl/core/typedef.hpp>
#include <xcal/render/impl/opengl/object/object.hpp>

#include "xcal/property/color.hpp"

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
namespace xcal::render::opengl {
class XCAL_API OpenGLRender : public xcal::render::Render {
    friend void ::framebuffer_size_callback(GLFWwindow* window, int w, int h);

   private:
    float_t aspect_ = 1.0f;
    property::Color background_color_ = property::Color(0.0f, 0.0f, 0.0f, 1.0f);
    GLFWwindow* window_ = nullptr;
    std::unordered_map<mobject::MObject*, object::object_ptr> objects_;

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
    float_t aspect() const { return aspect_; };
    float_t& aspect() { return aspect_; };
    property::Color& background_color() { return background_color_; };
    const property::Color& background_color() const {
        return background_color_;
    };
    std::vector<char> read_pixels_char() const;

   public:
    OpenGLRender(const OpenGLRender&) = delete;
    OpenGLRender& operator=(const OpenGLRender&) = delete;
    OpenGLRender(Scene* scene);
    virtual ~OpenGLRender() override;
};
}  // namespace xcal::render::opengl