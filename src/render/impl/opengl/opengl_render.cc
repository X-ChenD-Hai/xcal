#include <glad/glad.h>
//
#include <GLFW/glfw3.h>
#include <public.h>

#include <render/impl/opengl/opengl_render.hpp>
#define ROLE OpenGL
#define LABEL OpenGLRender
#include <utils/logmacrohelper.inc>

xcal::render::opengl::OpenGLRender::OpenGLRender(Scene* scene)
    : xcal::render::Render(scene) {
    _I("OpenGLRender created: " _SELF);
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
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        _E("Failed to initialize GLAD");
    }
    setup_scene();
}
xcal::render::opengl::OpenGLRender::~OpenGLRender() {

};
void xcal::render::opengl::OpenGLRender::show() {
    if (!window_) {
        _E("GLFW window is not created");
        return;
    }
    glfwMakeContextCurrent(window_);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
        render_frame();
    }
}
void xcal::render::opengl::OpenGLRender::render_frame() {
    glfwMakeContextCurrent(window_);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window_);
};
void xcal::render::opengl::OpenGLRender::set_scene(Scene* scene) {
    Render::set_scene(scene);
    setup_scene();
};
void xcal::render::opengl::OpenGLRender::setup_scene() {
    _I("setup_scene" << scene());
    objects_.clear();
    if (!scene()) {
        _W("scene is null");
        return;
    }
    for (auto& obj : scene()->mobjects()) {
        objects_.insert({obj.get(), object::create(obj.get())});
    }
};