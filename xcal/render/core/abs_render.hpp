#pragma once
#include <xcal/property/time_duration.hpp>
#include <xcal/property/time_point.hpp>
#include <xcal/render/core/context.hpp>
#include <xcal/scene/scene.hpp>
namespace xcal::render::opengl {
class OpenGLRender;
}
namespace xcal::render {
using GetProcAddress = void (*(*)(const char *))();
template <typename ObjectPtr = mobject::AbsMObject_ptr>
class XCAL_API AbsRender {
    friend class xcal::render::opengl::OpenGLRender;

   public:
    using Scene = scene::AbsScene<ObjectPtr>;

   private:
    Scene *scene_{nullptr};

   public:
    Scene *scene() const { return scene_; }

   public:
    virtual void set_scene(Scene *scene) = 0;
    virtual bool_t play_timeline(animation::Timeline *timeline) = 0;
    virtual void init(GetProcAddress get_proc_address) {};
    virtual void render_frame() = 0;
    virtual void before_render(int width, int height) {};
    virtual void after_render() {};
    virtual void frame_resize(int width, int height) {};

    virtual xcal::camera::AbsCamera *default_camera() const = 0;
    virtual const xcal::camera::AbsCamera *current_camera() const = 0;

   public:
    explicit AbsRender(scene::AbsScene<ObjectPtr> *scene) : scene_(scene) {}
    virtual ~AbsRender() {}

   public:
    AbsRender(const AbsRender &) = delete;
    AbsRender &operator=(const AbsRender &) = delete;
    AbsRender(AbsRender &&) = delete;
    AbsRender &operator=(AbsRender &&) = delete;
};
}  // namespace xcal::render