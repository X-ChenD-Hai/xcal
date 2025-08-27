#pragma once

#include <render/core/render.hpp>
#include <render/impl/opengl/core/typedef.hpp>
namespace xcal::render::opengl {
class OpenGLRender : public xcal::render::Render {
   private:
    GLFWwindow* window_ = nullptr;

   public:
    void show();
    void render();

   public:
    OpenGLRender(Scene* scene);
    virtual ~OpenGLRender() override;
};
}  // namespace xcal::render::opengl