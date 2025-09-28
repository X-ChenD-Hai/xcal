#include <GLFW/glfw3.h>

#include <xcal/render/impl/opengl/glfwrender.hpp>

#define ROLE GLFWRender
#define LABEL GLFWRender
#include <xcal/render/impl/opengl/utils/glfwdarkheadersupport.inc>
#include <xcal/utils/logmacrohelper.inc>

xcal::render::GLFWRender::GLFWRender(Scene* scene,
                                     RenderBackend* render_backend,
                                     UiContext* ui_context)
    : Render(scene, render_backend, ui_context) {
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
    glfwSetFramebufferSizeCallback(window_,
                                   [](GLFWwindow* window, int w, int h) {

                                   });
    glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode,
                                   int action, int mods) {
        if (key == GLFW_KEY_A) {
            if (action == GLFW_PRESS) {
                _D("A key pressed");
            } else if (action == GLFW_RELEASE) {
                _D("A key released");
            } else if (action == GLFW_REPEAT) {
                _D("A key repeated");
            }
        }
    });
    init();
}

void xcal::render::GLFWRender::show(int width, int height) {
    if (!window_) {
        _E("GLFW window is not created");
        return;
    }
    glfwSetWindowSize(window_, width, height);
    glfwMakeContextCurrent(window_);
}