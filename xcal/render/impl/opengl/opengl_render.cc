#include <xcal/render/impl/opengl/utils/openglapiloadhelper.inc>
//
#include <xcal/public.h>

#include <xcal/render/impl/opengl/opengl_render.hpp>
#include <xcal/render/impl/opengl/utils/glfwdarkheadersupport.inc>
#include <xcmath/utils/show.hpp>

//
#ifdef GL_BACKEND_GLBINDING
#    include <glbinding-aux/ContextInfo.h>
#    include <glbinding/gl/functions.h>
#    include <glbinding/glbinding.h>
#endif

//
#include <GLFW/glfw3.h>

#undef OUT  // undefine OUT macro to avoid conflict with xcal::OUT
#define ROLE OpenGL
#define LABEL OpenGLRender
#include <xcal/utils/logmacrohelper.inc>

constexpr static float_t kDDepth = 1;

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    static_cast<xcal::render::opengl::OpenGLRender*>(
        glfwGetWindowUserPointer(window))
        ->framebuffer_size_callback(window, w, h);
}

void init_glbackend() {
#ifdef GL_BACKEND_GLBINDING
    glbinding::initialize(glfwGetProcAddress, false);
#elif defined(GL_BACKEND_GLAD)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
#else
#    error "No OpenGL backend defined"
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
    _gl glEnable(_gl GL_DEPTH_TEST);
    _gl glDepthFunc(_gl GL_LESS);
    _gl glEnable(_gl GL_BLEND);
    _gl glBlendFunc(_gl GL_SRC_ALPHA, _gl GL_ONE_MINUS_SRC_ALPHA);
    glfwSetWindowUserPointer(window_, this);
    glfwSetFramebufferSizeCallback(window_, ::framebuffer_size_callback);
    // _gl glLineWidth(32.0f);
    setup_scene();
}
xcal::render::opengl::OpenGLRender::~OpenGLRender() {

};
void xcal::render::opengl::OpenGLRender::show(size_t width, size_t height) {
    if (!window_) {
        _E("GLFW window is not created");
        return;
    }
    glfwSetWindowSize(window_, width, height);
    glfwMakeContextCurrent(window_);
    _gl glClearColor(background_color_.r(), background_color_.g(),
                     background_color_.b(), background_color_.a());
    for (auto& obj : objects_) {
        obj.second->create();
    }
    ::framebuffer_size_callback(window_, width, height);
    _I("show loop started");
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
        _gl glClear(_gl GL_COLOR_BUFFER_BIT | _gl GL_DEPTH_BUFFER_BIT);
        render_frame();
        glfwSwapBuffers(window_);
    }
    _I("show loop ended");
    _I("destroying objects");
    for (auto& obj : objects_) obj.second->destroy();
    _I("objects destroyed ");
}
void xcal::render::opengl::OpenGLRender::render_frame() {
    if (!scene()->cameras().empty()) {
        const auto& cam = scene()->cameras().front();
        if (cam->should_update()) {
            for (auto& obj : objects_) {
                _D("updating object: " << obj.first
                                       << " with camera: " << cam.get());
                _D("pv_matrix: " << cam->pv_matrix());
                obj.second->update_projection_view(cam->pv_matrix());
            }
        }
    }
    for (const auto& obj : objects_) {
        auto& obj_ptr = obj.second;
        if (obj_ptr) {
            obj_ptr->render();
        }
    }
    // std::this_thread::sleep_for(std::chrono::milliseconds(300));
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
    _D("Number of mobjects in scene: " << scene()->mobjects().size());
    for (auto& obj : scene()->mobjects()) {
        _D("Processing mobject: " << obj.get());
        auto obj_ptr = object::create(obj.get());
        if (!obj_ptr) {
            _E("Failed to create object for " << obj.get());
            continue;
        }
        objects_.insert({obj.get(), std::move(obj_ptr)});
    }
};
void xcal::render::opengl::OpenGLRender::framebuffer_size_callback(
    GLFWwindow* window, int w, int h) {
    // _D("framebuffer_size_callback: " << w << "x" << h);

    // 计算保持宽高比的视口尺寸
    float target_aspect = aspect_;
    int viewport_width = w;
    int viewport_height = h;
    int viewport_x = 0;
    int viewport_y = 0;

    // 计算实际宽高比
    float actual_aspect = static_cast<float>(w) / static_cast<float>(h);

    if (actual_aspect > target_aspect) {
        // 窗口太宽，上下加黑边
        viewport_width = static_cast<int>(h * target_aspect);
        viewport_height = h;
        viewport_x = (w - viewport_width) / 2;
        viewport_y = 0;
    } else {
        // 窗口太高，左右加黑边
        viewport_width = w;
        viewport_height = static_cast<int>(w / target_aspect);
        viewport_x = 0;
        viewport_y = (h - viewport_height) / 2;
    }

    // 设置视口
    _gl glViewport(viewport_x, viewport_y, viewport_width, viewport_height);
    _gl glClearColor(background_color_.r(), background_color_.g(),
                     background_color_.b(), background_color_.a());

    // _D("Viewport set to: " << viewport_x << ", " << viewport_y << ", "
    //                        << viewport_width << ", " << viewport_height);
}
