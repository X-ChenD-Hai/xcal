
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
#include <xcal/render/impl/opengl/openglrender.hpp>
#include <xcal/render/impl/ui/imguiglfw3opengl3backend.hpp>
#include <xcal/render/impl/ui/listui.hpp>
#include <xcmath/utils/show.hpp>

//
#ifdef GL_BACKEND_GLBINDING
#    include <glbinding-aux/ContextInfo.h>
#    include <glbinding/gl/functions.h>
#    include <glbinding/glbinding.h>
#endif

#define ROLE OpenGL
#define LABEL OpenGLRender
#include <xcal/utils/logmacrohelper.inc>

void xcal::render::OpenGLRender::render_frame() {
    _gl glClear(_gl GL_COLOR_BUFFER_BIT | _gl GL_DEPTH_BUFFER_BIT);
    if (objects_.empty()) return;
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
            auto& m = current_camera_->pv_matrix();
            for (auto& obj : objects_) {
                _D("updating object: " << obj.first
                                       << " with camera: " << current_camera_);
                _D("pvurcurrent_camera_atrix: "
                   << current_camera_->pv_matrix());
                obj.second->update_projection_view(m);
            }
        }
    }
    for (const auto& obj : objects_) {
        auto& obj_ptr = obj.second;
        if (obj_ptr) {
            obj_ptr->render();
        }
    }
}
xcal::bool_t xcal::render::OpenGLRender::play_timeline(
    animation::Timeline* timeline) {
    if (playing_timeline_ && !playing_timeline_->finished()) return false;
    _I("play_timeline: " << timeline);
    playing_timeline_ = std::make_unique<animation::TimelineDriver>(timeline);
    playing_timeline_->ready_to_play();
    return true;
}
void xcal::render::OpenGLRender::init(GetProcAddress get_proc_address) {
#ifdef GL_BACKEND_GLBINDING
    glbinding::initialize(get_proc_address, false);
#elif defined(GL_BACKEND_GLAD)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
#else
#    error "No OpenGL backend defined"
#endif
    _gl glEnable(_gl GL_DEPTH_TEST);
    _gl glDepthFunc(_gl GL_LESS);
    _gl glEnable(_gl GL_BLEND);
    _gl glBlendFunc(_gl GL_SRC_ALPHA, _gl GL_ONE_MINUS_SRC_ALPHA);
}
xcal::render::OpenGLRender::~OpenGLRender() { deinit(); }
void xcal::render::OpenGLRender::frame_resize(int w, int h) {
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
}
void xcal::render::OpenGLRender::set_scene(Scene* scene) {
    Render::set_scene(scene);
};
void xcal::render::OpenGLRender::setup_scene() {
    _I("setup_scene" << scene());
    objects_.clear();
    if (!scene()) {
        _W("scene is null");
        return;
    }
    _D("Number of mobjects in scene: " << scene()->mobjects().size());
    for (auto& obj : scene()->mobjects()) {
        _D("Processing mobject: " << obj.get());
        auto obj_ptr = opengl::object::create(obj.get());
        if (!obj_ptr) {
            _E("Failed to create object for " << obj.get());
            continue;
        }
        objects_.insert({obj.get(), std::move(obj_ptr)});
    }
};
void xcal::render::OpenGLRender::before_render(int w, int h) {
    _I("before_render");
    setup_scene();
    frame_resize(w, h);
    for (const auto& obj : objects_) obj.second->create();
}
void xcal::render::OpenGLRender::after_render() {
    _I("after_render");
    for (const auto& obj : objects_) obj.second->destroy();
}
xcal::render::OpenGLRender::OpenGLRender(Scene* scene)
    : Render(scene),
      default_camera_(std::make_unique<xcal::camera::PerspectiveCamera>(
          45.0, 16 / 9.0, 0.1, 1000.0)),
      current_camera_(default_camera_.get()) {}
