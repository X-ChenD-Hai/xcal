#include <xcal/render/impl/opengl/utils/glbindingincludehelper.inc>
//
#include <GLFW/glfw3.h>
#include <glbinding-aux/ContextInfo.h>
#include <glbinding/glbinding.h>
#include <xcal/public.h>

#include <xcal/render/impl/opengl/opengl_render.hpp>

#define ROLE OpenGL
#define LABEL OpenGLRender
#include <xcal/utils/logmacrohelper.inc>
void init_glbinding() {
    glbinding::initialize(glfwGetProcAddress, false);
    std::cout << "OpenGL context: "
              << glbinding::aux::ContextInfo::version().toString() << '\n';
}
#include <xcal/utils/logmacrohelper.inc>

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
    init_glbinding();
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
    _gl glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    for (auto& obj : objects_) obj.second->create();
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
    glClear(_gl GL_COLOR_BUFFER_BIT);

    for (auto& obj : objects_) {
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