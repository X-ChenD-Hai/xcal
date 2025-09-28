#include <xcal/render/impl/opengl/utils/openglapiloadhelper.inc>
//
#include <xcal/public.h>

#include <cstddef>
#include <cstdio>
#include <memory>
#include <xcal/camera/core/abs_camera.hpp>
#include <xcal/camera/perspectivecamera.hpp>
#include <xcal/mobject/core/mobject_types.hpp>
#include <xcal/render/impl/opengl/core/typedef.hpp>
#include <xcal/render/impl/opengl/opengl_render.hpp>
#include <xcal/render/impl/opengl/ui/imguiglfw3opengl3backend.hpp>
#include <xcal/render/impl/opengl/ui/listui.hpp>
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
    : xcal::render::Render(scene),
      ui_render_(nullptr),
      default_camera_(std::make_unique<xcal::camera::PerspectiveCamera>(
          45.0, 16 / 9.0, 0.1, 1000.0)),
      current_camera_(default_camera_.get()) {
    _I("OpenGLRender created: " _SELF);
    setup_glfw();
    setup_gl();
    ui_render_ = std::make_unique<ui::ListUi>(
        std::make_unique<ui::ImGuiGlfw3OpenGL3Backend>(window_), this);
    ui_render_->init();
    setup_scene();
}
xcal::render::opengl::OpenGLRender::~OpenGLRender() {
    ui_render_->deinit();
    objects_.clear();

    if (window_) {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
    glfwTerminate();
    _I("OpenGLRender destroyed: " _SELF);
};
void xcal::render::opengl::OpenGLRender::show(int width, int height) {
    if (!window_) {
        _E("GLFW window is not created");
        return;
    }
    glfwSetWindowSize(window_, width, height);
    glfwMakeContextCurrent(window_);
    for (auto& obj : objects_) {
        obj.second->create();
    }
    ::framebuffer_size_callback(window_, width, height);
    _I("show loop started");
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
        // begin_frame();
        if (ui_render_) ui_render_->render_();

        _gl glClear(_gl GL_COLOR_BUFFER_BIT | _gl GL_DEPTH_BUFFER_BIT);
        render_frame();
        // end_frame();
        if (ui_render_) ui_render_->before_swap_buffers();

        glfwSwapBuffers(window_);
    }
    _I("show loop ended");
    _I("destroying objects");
    for (auto& obj : objects_) obj.second->destroy();
    _I("objects destroyed ");
}
void xcal::render::opengl::OpenGLRender::render_frame() {
    if (playing_timeline_ && !playing_timeline_->finished()) {
        if (auto n = std::chrono::high_resolution_clock::now();
            n - last_time_point_ >
            std::chrono::milliseconds(
                size_t(1000 / playing_timeline_->frame_rate()))) {
            playing_timeline_->next();
            last_time_point_ = n;
        }
    }
    if (current_camera_) {
        if (current_camera_->should_update()) {
            for (auto& obj : objects_) {
                _D("updating object: " << obj.first
                                       << " with camera: " << current_camera_);
                _D("pvurcurrent_camera_atrix: "
                   << current_camera_->pv_matrix());
                obj.second->update_projection_view(
                    current_camera_->pv_matrix());
            }
        }
    }
    for (const auto& obj : objects_) {
        auto& obj_ptr = obj.second;
        if (obj_ptr) {
            obj_ptr->render();
        }
    }
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
    ui_render_->flush();
};
void xcal::render::opengl::OpenGLRender::framebuffer_size_callback(GLFWwindow*,
                                                                   int w,
                                                                   int h) {
    // aspect_ = w / static_cast<float>(h);
    if (default_camera_->type() == camera::CameraType::Perspective) {
        auto* cam = static_cast<xcal::camera::PerspectiveCamera*>(
            default_camera_.get());
        cam->set_aspect((float_t)w / static_cast<float>(h));
    }

    // _D("framebuffer_size_callback: " << w << "x" << h);
    // 计算保持宽高比的视口尺寸
    float target_aspect =
        (current_camera_->type() == camera::CameraType::Perspective)
            ? ((const camera::PerspectiveCamera*)current_camera_)
                  ->aspect()
                  .value()
            : (float_t)w / static_cast<float>(h);
    int viewport_width = w;
    int viewport_height = h;
    int viewport_x = 0;
    int viewport_y = 0;

    // 计算实际宽高比
    float actual_aspect = static_cast<float>(w) / static_cast<float>(h);

    if (actual_aspect > target_aspect) {
        // 窗口太宽，上下加黑边
        viewport_width = static_cast<int>((float_t)h * target_aspect);
        viewport_height = h;
        viewport_x = (w - viewport_width) / 2;
        viewport_y = 0;
    } else {
        // 窗口太高，左右加黑边
        viewport_width = w;
        viewport_height = static_cast<int>((float_t)w / target_aspect);
        viewport_x = 0;
        viewport_y = (h - viewport_height) / 2;
    }

    // 设置视口
    _gl glViewport(viewport_x, viewport_y, viewport_width, viewport_height);
    _gl glClearColor(current_camera_->background_color().r(),
                     current_camera_->background_color().g(),
                     current_camera_->background_color().b(),
                     current_camera_->background_color().a());

    // _D("Viewport set to: " << viewport_x << ", " << viewport_y << ", "
    //                        << viewport_width << ", " << viewport_height);
}
std::vector<char> xcal::render::opengl::OpenGLRender::read_pixels_char() const {
    _gl GLint width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    std::vector<char> pixels(width * height * 4);  // RGBA
    _gl glReadPixels(0, 0, width, height, _gl GL_RGBA, _gl GL_UNSIGNED_BYTE,
                     pixels.data());
    std::cerr << "Read: " << width << "x" << height << " pixels\n";
    return pixels;
}
void xcal::render::opengl::OpenGLRender::setup_glfw() {
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
    glfwSetFramebufferSizeCallback(window_, ::framebuffer_size_callback);
    glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode,
                                   int action, int mods) {
        auto& render = *static_cast<xcal::render::opengl::OpenGLRender*>(
            glfwGetWindowUserPointer(window));
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
};
void xcal::render::opengl::OpenGLRender::setup_gl() {
    init_glbackend();
    _gl glEnable(_gl GL_DEPTH_TEST);
    _gl glDepthFunc(_gl GL_LESS);
    _gl glEnable(_gl GL_BLEND);
    _gl glBlendFunc(_gl GL_SRC_ALPHA, _gl GL_ONE_MINUS_SRC_ALPHA);
};
xcal::bool_t xcal::render::opengl::OpenGLRender::play_timeline(
    animation::Timeline* timeline) {
    if (playing_timeline_ && !playing_timeline_->finished()) return false;
    _I("play_timeline: " << timeline);
    playing_timeline_ = std::make_unique<animation::TimelineDriver>(timeline);
    playing_timeline_->ready_to_play();
    return true;
}
