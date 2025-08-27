#include <glad/glad.h>
//
#include <GLFW/glfw3.h>
#include <public.h>

#include <render/impl/opengl/opengl_render.hpp>

xcal::render::opengl::OpenGLRender::OpenGLRender(Scene* scene)
    : xcal::render::Render(scene) {
    XCAL_INFO(OpenGLRender, OpenGL) << "OpenGLRender created";
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if (window_ == nullptr) {
        glfwTerminate();
        XCAL_ERROR(OpenGLRender, OpenGL) << "Failed to create GLFW window";
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        XCAL_ERROR(OpenGLRender, OpenGL) << "Failed to initialize GLAD";
    }
}
xcal::render::opengl::OpenGLRender::~OpenGLRender() {

};
void xcal::render::opengl::OpenGLRender::show() {
    if (!window_) {
        XCAL_ERROR(OpenGLRender, OpenGL) << "GLFW window is not created";
        return;
    }
    glfwMakeContextCurrent(window_);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
        render();
    }
}
void xcal::render::opengl::OpenGLRender::render() {
    glfwMakeContextCurrent(window_);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window_);
};