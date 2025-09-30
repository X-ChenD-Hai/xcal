#include <GLFW/glfw3.h>

#include <frontends/ui/imgui/listui.hpp>
#include <glfwrender.hpp>
#include <imguiglfw3opengl3backend.hpp>
#include <print>

#define ROLE GLFWRender
#define LABEL GLFWRender
#include <glfwdarkheadersupport.inc>
#include <xcal/utils/logmacrohelper.inc>

static inline xcal::render::GLFWRender* GetSelf(GLFWwindow* window) {
    return static_cast<xcal::render::GLFWRender*>(
        glfwGetWindowUserPointer(window));
}

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
    glfwSetCursorPosCallback(window_, cursor_pos_callback);
    glfwSetScrollCallback(window_, scroll_callback);
    glfwSetMouseButtonCallback(window_, mouse_button_callback);
    render_ = render;
    render_->init(glfwGetProcAddress);
    std::println("GLFWRender initialized");
    ui_render_ = std::make_unique<ui::ListUi>(
        std::make_unique<ui::ImGuiGlfw3OpenGL3Backend>(window_), render_);
    std::println("ImGui initialized");
    ui_render_->init();
    std::println("ImGui backend initialized");
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
                                            int /*scancode*/, int action,
                                            int mods) {
    auto self = GetSelf(window);
    if (mods != 0 || self->ui_render_->want_capture_keyboard()) return;
    auto& fps_camera_controler =
        static_cast<GLFWRender*>(glfwGetWindowUserPointer(window))
            ->ui_render_->fps_camera_controler();
    static constexpr float_t MOVE_SPEED = 0.02f;
    uint8_t direction = 0;
    switch (key) {
        case GLFW_KEY_A:
            direction = (uint8_t)camera::FpsCameraControler::Direction::LEFT;
            break;
        case GLFW_KEY_D:
            direction = (uint8_t)camera::FpsCameraControler::Direction::RIGHT;
            break;
        case GLFW_KEY_W:
            direction = (uint8_t)camera::FpsCameraControler::Direction::FORWARD;
            break;
        case GLFW_KEY_S:
            direction =
                (uint8_t)camera::FpsCameraControler::Direction::BACKWARD;
            break;
        case GLFW_KEY_Q:
            direction = (uint8_t)camera::FpsCameraControler::Direction::UP;
            break;
        case GLFW_KEY_E:
            direction = (uint8_t)camera::FpsCameraControler::Direction::DOWN;
            break;
        default:
            break;
    }
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        _D("W key pressed");
        fps_camera_controler.move(
            camera::FpsCameraControler::Direction(direction), MOVE_SPEED);
    }
}
void xcal::render::GLFWRender::set_render(Render* render) {
    render_ = render;
    render_->init(glfwGetProcAddress);
}
void xcal::render::GLFWRender::cursor_pos_callback(GLFWwindow* window,
                                                   double xpos, double ypos) {
    auto self = GetSelf(window);
    if (self->ui_render_->want_capture_mouse()) return;
    static constexpr float_t ROTATE_SPEED = 0.2f;
    if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) &&
        self->mouse_move_flag_) {
        _D("mouse left button pressed and moved"
           << std::format("offset ({}, {})", xpos - self->last_mouse_x_,
                          ypos - self->last_mouse_y_));
        self->ui_render_->fps_camera_controler().rotate(
            float_t(xpos - self->last_mouse_x_) * ROTATE_SPEED,
            -float_t(ypos - self->last_mouse_y_) * ROTATE_SPEED);
        self->last_mouse_x_ = xpos;
        self->last_mouse_y_ = ypos;
    }
}
void xcal::render::GLFWRender::scroll_callback(GLFWwindow* window,
                                               double xoffset, double yoffset) {
}
void xcal::render::GLFWRender::mouse_button_callback(GLFWwindow* window,
                                                     int button, int action,
                                                     int mods) {
    auto self = GetSelf(window);
    if (self->ui_render_->want_capture_mouse()) return;
    if (mods == 0)
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
                self->mouse_move_flag_ = true;
                glfwGetCursorPos(window, &self->last_mouse_x_,
                                 &self->last_mouse_y_);
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            } else if (action == GLFW_RELEASE) {
                self->mouse_move_flag_ = false;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
}
