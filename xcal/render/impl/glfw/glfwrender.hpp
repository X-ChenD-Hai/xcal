#pragma once
#include <xcal/render/core/render.hpp>
struct GLFWwindow;
namespace xcal::render {
class XCAL_API GLFWRender {
   private:
    GLFWwindow* window_{nullptr};
    Render* render_{nullptr};
    std::unique_ptr<ui::Context> ui_render_{nullptr};
    double last_mouse_x_{0.0};
    double last_mouse_y_{0.0};
    bool mouse_move_flag_{false};

   public:
    explicit GLFWRender(Render* render);
    ~GLFWRender();

   public:
    void set_render(Render* render);
    void show(int width, int height);

   private:
    static void mouse_button_callback(GLFWwindow* window, int button,
                                      int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset,
                                double yoffset);
    static void cursor_pos_callback(GLFWwindow* window, double xpos,
                                    double ypos);
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