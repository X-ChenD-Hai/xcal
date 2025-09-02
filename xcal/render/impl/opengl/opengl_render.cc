#include <xcal/render/impl/opengl/utils/openglapiloadhelper.inc>
//
#include <xcal/public.h>

#include <xcal/render/impl/opengl/opengl_render.hpp>
#include <xcal/render/impl/opengl/utils/glfwdarkheadersupport.inc>
//
#ifdef GL_BACKEND_GLBINDING
#include <glbinding-aux/ContextInfo.h>
#include <glbinding/gl/functions.h>
#include <glbinding/glbinding.h>
#endif

//
#include <GLFW/glfw3.h>

#undef OUT  // undefine OUT macro to avoid conflict with xcal::OUT
#define ROLE OpenGL
#define LABEL OpenGLRender
#include <xcal/utils/logmacrohelper.inc>

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    (w > h) ? _gl glViewport((w - h) / 2, 0, h, h)
            : _gl glViewport(0, (h - w) / 2, w, w);
}

void init_glbackend() {
#ifdef GL_BACKEND_GLBINDING
    glbinding::initialize(glfwGetProcAddress, false);
#elif defined(GL_BACKEND_GLAD)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
#else
#error "No OpenGL backend defined"
#endif
}

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
    if (!enable_window_dark_titlebar(window_)) {
        _D("Failed to enable dark titlebar");
    }
    init_glbackend();
    // _gl glLineWidth(32.0f);
    setup_scene();
}
xcal::render::opengl::OpenGLRender::~OpenGLRender(){

};
void xcal::render::opengl::OpenGLRender::show(size_t width, size_t height) {
    if (!window_) {
        _E("GLFW window is not created");
        return;
    }
    glfwSetWindowSize(window_, width, height);
    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
    _gl glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    for (auto& obj : objects_) obj.second->create();
    framebuffer_size_callback(window_, width, height);
    _I("show loop started");
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
        render_frame();
    }
    _I("show loop ended");
    _I("destroying objects");
    for (auto& obj : objects_) obj.second->destroy();
    _I("objects destroyed ");
}
void xcal::render::opengl::OpenGLRender::render_frame() {
    glfwMakeContextCurrent(window_);
    _gl glClear(_gl GL_COLOR_BUFFER_BIT);

    for (const auto& obj : objects_) {
        auto& obj_ptr = obj.second;
        if (obj_ptr) {
            obj_ptr->render();
        }
    }

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
        auto obj_ptr = object::create(obj.get());
        if (!obj_ptr) {
            _E("Failed to create object for " << obj.get());
            continue;
        }
        objects_.insert({obj.get(), std::move(obj_ptr)});
    }
};