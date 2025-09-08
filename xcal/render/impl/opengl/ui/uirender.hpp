
#pragma once

#include <xcal/public.h>

#include <xcal/camera/core/abs_camera.hpp>
#include <xcal/mobject/core/mobject.hpp>

namespace xcal::render::opengl {
class OpenGLRender;
}
namespace xcal::render::opengl::ui {
class UIRender {
    struct ObjectHandle {
        using mobject_t = xcal::mobject::MObject;
        mobject_t* obj;
        std::string name;
        std::string type;
        ObjectHandle(mobject_t* obj);
    };
    struct CameraHandle {
        using camera_t = xcal::camera::AbsCamera;
        camera_t* camera;
        std::string name;
        CameraHandle(camera_t* camera);
        CameraHandle(camera_t* camera, const std::string& name);
    };

    bool show_ = true;
    std::vector<ObjectHandle> object_handles_{};
    std::vector<CameraHandle> camera_handles_{};
    CameraHandle default_camera_handles_{nullptr, "default"};
    OpenGLRender* renderer_{nullptr};
    float_t tmp_;
    xcmath::vec3<float_t> vec3f_tmp_;

   protected:
    void render_obj(ObjectHandle& obj);
    void render_camera(CameraHandle& cam);
    bool render_vec3f_edit(const xcmath::vec3<float_t>& vec3f,
                           const char* label, const char* x_label = "x",
                           const char* y_label = "y",
                           const char* z_label = "z");

   public:
    UIRender(OpenGLRender* renderer);
    void init();
    void deinit();
    void flush();
    void render();
    void render_ui();
    void before_swap_buffers();
};
}  // namespace xcal::render::opengl::ui