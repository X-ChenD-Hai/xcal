#pragma once
#include <xcal/property/time_duration.hpp>
#include <xcal/property/time_point.hpp>
#include <xcal/scene/scene.hpp>

namespace xcal::render {
template <typename ObjectPtr = mobject::AbsMObject_ptr>
class XCAL_API AbsRender {
   public:
    using Scene = scene::AbsScene<ObjectPtr>;

   private:
    Scene *scene_ = nullptr;

   public:
    virtual void set_scene(Scene *scene);
    Scene *scene() const { return scene_; }

   public:
    explicit AbsRender(scene::AbsScene<ObjectPtr> *scene) : scene_(scene) {}
    virtual ~AbsRender() = default;
};
}  // namespace xcal::render