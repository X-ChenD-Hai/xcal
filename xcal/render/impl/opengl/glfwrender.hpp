#pragma once
#include <xcal/render/core/render.hpp>
struct GLFWwindow;
namespace xcal::render {
class XCAL_API GLFWRender {
   private:
    GLFWwindow* window_{nullptr};
    Render* render_{nullptr};
    std::unique_ptr<Context> ui_render_{nullptr};

   public:
    explicit GLFWRender(Render* render);
    ~GLFWRender();

   public:
    void set_render(Render* render);
    void show(int width, int height);

   private:
    static void framebuffer_size_callback(GLFWwindow* window, int w, int h);
    static void key_callback(GLFWwindow* window, int key, int scancode,
                             int action, int mods);

   public:
    GLFWRender(const GLFWRender&) = delete;
    GLFWRender(GLFWRender&&) = delete;
    GLFWRender& operator=(const GLFWRender&) = delete;
    GLFWRender& operator=(GLFWRender&&) = delete;
};
}  // namespace xcal::render