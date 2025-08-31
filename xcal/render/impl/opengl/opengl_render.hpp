#pragma once
#include <unordered_map>
#include <xcal/render/core/render.hpp>
#include <xcal/render/impl/opengl/core/typedef.hpp>
#include <xcal/render/impl/opengl/object/object.hpp>

namespace xcal::render::opengl {
class OpenGLRender : public xcal::render::Render {
   private:
    GLFWwindow* window_ = nullptr;
    std::unordered_map<mobject::MObject*, object::object_ptr> objects_;

   private:
    void setup_scene();

   public:
    void show();
    void render_frame();
    virtual void set_scene(Scene* scene) override;

   public:
    OpenGLRender(Scene* scene);
    virtual ~OpenGLRender() override;
};
}  // namespace xcal::render::opengl