#include <GLFW/glfw3.h>

#include <xcal/render/impl/opengl/glfwrender.hpp>
#include <xcal/render/impl/opengl/ui/imguiglfw3opengl3backend.hpp>
#include <xcal/render/impl/opengl/ui/listui.hpp>

#define ROLE GLFWRender
#define LABEL GLFWRender
#include <xcal/render/impl/opengl/utils/glfwdarkheadersupport.inc>
#include <xcal/utils/logmacrohelper.inc>

#include "glfwrender.hpp"

xcal::render::GLFWRender::GLFWRender(Render* render)
    : window_(nullptr), render_(render), ui_render_(nullptr) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window_ = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if (window_ == nullptr) {
        glfwTerminate();
        _D("Failed to create GLFW window");
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window_);
    if (!enable_window_dark_titlebar(window_)) {
        _D("Failed to enable dark titlebar");
    }
    glfwSetWindowUserPointer(window_, this);
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
    glfwSetKeyCallback(window_, key_callback);
    render_ = render;
    render_->init(glfwGetProcAddress);
    ui_render_ = std::make_unique<opengl::ui::ListUi>(
        std::make_unique<opengl::ui::ImGuiGlfw3OpenGL3Backend>(window_),
        render_);
    ui_render_->init();
}

xcal::render::GLFWRender::~GLFWRender() {
    ui_render_->deinit();
    render_->deinit();
    if (window_) {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
    glfwTerminate();
}
void xcal::render::GLFWRender::show(int width, int height) {
    if (!window_) {
        _E("GLFW window is not created");
        return;
    }
    glfwSetWindowSize(window_, width, height);
    glfwMakeContextCurrent(window_);

    _I("show loop started");
    render_->before_render(width, height);
    ui_render_->flush();
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
        ui_render_->render_frame();
        render_->render_frame();
        ui_render_->before_swap_buffers();
        glfwSwapBuffers(window_);
    }
    render_->after_render();
    _I("show loop ended");
}
void xcal::render::GLFWRender::framebuffer_size_callback(GLFWwindow* window,
                                                         int w, int h) {
    static_cast<GLFWRender*>(glfwGetWindowUserPointer(window))
        ->render_->frame_resize(w, h);
}
void xcal::render::GLFWRender::key_callback(GLFWwindow* window, int key,
                                            int scancode, int action,
                                            int mods) {
    if (key == GLFW_KEY_A) {
        if (action == GLFW_PRESS) {
            _D("A key pressed");
        } else if (action == GLFW_RELEASE) {
            _D("A key released");
        } else if (action == GLFW_REPEAT) {
            _D("A key repeated");
        }
    }
}
void xcal::render::GLFWRender::set_render(Render* render) {
    render_ = render;
    render_->init(glfwGetProcAddress);
}
