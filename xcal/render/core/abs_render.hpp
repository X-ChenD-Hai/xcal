#pragma once
#include <xcal/property/time_duration.hpp>
#include <xcal/property/time_point.hpp>
#include <xcal/render/core/context.hpp>
#include <xcal/scene/scene.hpp>
namespace xcal::render::opengl {
class OpenGLRender;
}
namespace xcal::render {
template <typename ObjectPtr = mobject::AbsMObject_ptr>
class XCAL_API AbsRender {
    friend class xcal::render::opengl::OpenGLRender;

   public:
    using Scene = scene::AbsScene<ObjectPtr>;

   private:
    Scene *scene_ = nullptr;
    std::unique_ptr<Context> ui_render_{nullptr};

   public:
    Scene *scene() const { return scene_; }
    // void begin_frame() {
    //     if (ui_render_) ui_render_->render_();
    // }
    // void end_frame() {
    //     if (ui_render_) ui_render_->before_swap_buffers();
    // }
    virtual void set_scene(Scene *scene);
    virtual bool_t play_timeline(animation::Timeline *timeline) = 0;
    virtual xcal::camera::AbsCamera *default_camera() const = 0;
    virtual const xcal::camera::AbsCamera *current_camera() const = 0;

   public:
    explicit AbsRender(scene::AbsScene<ObjectPtr> *scene) : scene_(scene) {}
    // AbsRender(scene::AbsScene<ObjectPtr> *scene, std::unique_ptr<Context > ui)
    //     : scene_(scene), ui_render_(ui) {}

    virtual ~AbsRender() {

    };

   public:
    AbsRender(const AbsRender &) = delete;
    AbsRender &operator=(const AbsRender &) = delete;
    AbsRender(AbsRender &&) = delete;
    AbsRender &operator=(AbsRender &&) = delete;
};
}  // namespace xcal::render