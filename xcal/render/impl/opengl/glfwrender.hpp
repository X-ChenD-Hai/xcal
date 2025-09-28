#pragma once
#include <xcal/render/core/render_.hpp>
struct GLFWwindow;
namespace xcal::render {
class GLFWRender : public xcal::render::Render<> {
   public:
    using Render<>::Render;
    using Render<>::Scene;

   private:
    GLFWwindow* window_{nullptr};

   public:
    GLFWRender(Scene* scene, RenderBackend* render_backend,
               UiContext* ui_context);

   public:
    void show(int width, int height);
};
}  // namespace xcal::render